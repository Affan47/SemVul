wakeup_source_add(struct wakeup_source *ws)
{
	unsigned long flags;

	if (WARN_ON(!ws))
		return;

	spin_lock_init(&ws->lock);
	setup_timer(&ws->timer, pm_wakeup_timer_fn, (unsigned long)ws);
	ws->active = false;
	ws->last_time = ktime_get();

	spin_lock_irqsave(&events_lock, flags);
	list_add_rcu(&ws->entry, &wakeup_sources);
	spin_unlock_irqrestore(&events_lock, flags);
}
