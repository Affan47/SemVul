event_callback_activate_later_nolock_(struct event_base *base,
    struct event_callback *evcb)
{
	if (evcb->evcb_flags & (EVLIST_ACTIVE|EVLIST_ACTIVE_LATER))
		return;

	event_queue_insert_active_later(base, evcb);
	if (EVBASE_NEED_NOTIFY(base))
		evthread_notify_base(base);
}
