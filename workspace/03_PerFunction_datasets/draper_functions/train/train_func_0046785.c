dump_inserted_event_fn(const struct event_base *base, const struct event *e, void *arg)
{
	FILE *output = arg;
	const char *gloss = (e->ev_events & EV_SIGNAL) ?
	    "sig" : "fd ";

	if (! (e->ev_flags & (EVLIST_INSERTED|EVLIST_TIMEOUT)))
		return 0;

	fprintf(output, "  %p [%s "EV_SOCK_FMT"]%s%s%s%s%s",
	    (void*)e, gloss, EV_SOCK_ARG(e->ev_fd),
	    (e->ev_events&EV_READ)?" Read":"",
	    (e->ev_events&EV_WRITE)?" Write":"",
	    (e->ev_events&EV_SIGNAL)?" Signal":"",
	    (e->ev_events&EV_PERSIST)?" Persist":"",
	    (e->ev_flags&EVLIST_INTERNAL)?" Internal":"");
	if (e->ev_flags & EVLIST_TIMEOUT) {
		struct timeval tv;
		tv.tv_sec = e->ev_timeout.tv_sec;
		tv.tv_usec = e->ev_timeout.tv_usec & MICROSECONDS_MASK;
		evutil_timeradd(&tv, &base->tv_clock_diff, &tv);
		fprintf(output, " Timeout=%ld.%06d",
		    (long)tv.tv_sec, (int)(tv.tv_usec & MICROSECONDS_MASK));
	}
	fputc('\n', output);

	return 0;
}
