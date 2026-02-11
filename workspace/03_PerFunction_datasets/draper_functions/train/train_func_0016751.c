mod_timer(struct timer_list *timer, unsigned long expires)
{
	expires = apply_slack(timer, expires);


	if (timer_pending(timer) && timer->expires == expires)
		return 1;

	return __mod_timer(timer, expires, false, TIMER_NOT_PINNED);
}
