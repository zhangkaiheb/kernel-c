#include <linux/module.h>

static struct timer_list k_timer;

static void expire_timeout(unsigned long unused)
{
	struct timeval start_tv;

	do_gettimeofday(&start_tv);

	printk("%s tv_sec %ld.%ld\n",
			__func__, start_tv.tv_sec, start_tv.tv_usec);

	mod_timer(&k_timer, jiffies + 3*HZ);
}

static int k_timer_init(void)
{
	setup_timer(&k_timer, expire_timeout, 0);

	k_timer.expires  = jiffies + 3*HZ;
	add_timer(&k_timer);

	return 0;
}

static int __init timer_init(void)
{
	k_timer_init();
	return 0;
}

static void __exit timer_exit(void)
{
	del_timer_sync(&k_timer);
}

module_init(timer_init);
module_exit(timer_exit);

