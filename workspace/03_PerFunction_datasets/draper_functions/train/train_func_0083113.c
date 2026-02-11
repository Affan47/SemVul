event_initialized(const struct event *ev)
{
	if (!(ev->ev_flags & EVLIST_INIT))
		return 0;

	return 1;
}
