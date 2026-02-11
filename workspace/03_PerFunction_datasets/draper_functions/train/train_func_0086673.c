timer_remove_event(struct event *ev)
{
	LOG_DBG((LOG_TIMER, 10, "timer_remove_event: removing event %s(%p)",
	    ev->name, ev->arg));
	TAILQ_REMOVE(&events, ev, link);
	free(ev);
}
