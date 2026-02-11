snd_seq_timer_get_cur_time(struct snd_seq_timer *tmr)
{
	snd_seq_real_time_t cur_time;
	unsigned long flags;

	spin_lock_irqsave(&tmr->lock, flags);
	cur_time = tmr->cur_time;
	if (tmr->running) {
		struct timeval tm;
		int usec;
		do_gettimeofday(&tm);
		usec = (int)(tm.tv_usec - tmr->last_update.tv_usec);
		if (usec < 0) {
			cur_time.tv_nsec += (1000000 + usec) * 1000;
			cur_time.tv_sec += tm.tv_sec - tmr->last_update.tv_sec - 1;
		} else {
			cur_time.tv_nsec += usec * 1000;
			cur_time.tv_sec += tm.tv_sec - tmr->last_update.tv_sec;
		}
		snd_seq_sanity_real_time(&cur_time);
	}
	spin_unlock_irqrestore(&tmr->lock, flags);
	return cur_time;
}
