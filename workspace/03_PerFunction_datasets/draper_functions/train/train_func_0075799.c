dvr_init_stat_timer(struct adapter_s *a) {
	struct timeval	tv;

	if (!a->dvr.stat.interval)
		return;

	a->dvr.stat.last=time(NULL);

	tv.tv_sec=a->dvr.stat.interval;
	tv.tv_usec=0;

	evtimer_set(&a->dvr.stat.event, dvr_stat_timer, a);
	evtimer_add(&a->dvr.stat.event, &tv);
}
