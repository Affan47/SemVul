event_add_subscriber(struct event *evt, GCallback cb,
	enum frequency_type t, uint32 interval)
{
    struct subscriber *s;
	GSList *sl;

    g_assert(evt != NULL);
    g_assert(cb != NULL);

	for (sl = evt->subscribers; sl; sl = g_slist_next(sl)) {
		s = sl->data;
		g_assert(s->cb != cb);
	}

    s = subscriber_new(cb, t, interval);
    evt->subscribers = g_slist_append(evt->subscribers, s);
}
