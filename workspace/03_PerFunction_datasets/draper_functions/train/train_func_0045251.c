ksz_init_timer(struct ksz_timer_info *info, int period,
	void (*function)(unsigned long), void *data)
{
	info->max = 0;
	info->period = period;
	setup_timer(&info->timer, function, (unsigned long)data);
}
