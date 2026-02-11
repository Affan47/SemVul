shutdown_7220_relock_poll(struct qib_devdata *dd)
{
	if (dd->cspec->relock_timer_active)
		del_timer_sync(&dd->cspec->relock_timer);
}
