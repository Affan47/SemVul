cancel_timeout (where, what)
	void (*where) (void *);
	void *what;
{
	struct timeout *t, *q;


	t = (struct timeout *)0;
	for (q = timeouts; q; q = q -> next) {
		if (q->func == where && q->what == what) {
			if (t)
				t->next = q->next;
			else
				timeouts = q->next;
			break;
		}
		t = q;
	}


	if (q) {
#if defined (TRACING)
		if (!trace_playback()) {
#endif
			isc_timer_detach(&q->isc_timeout);
#if defined (TRACING)
		}
#endif

		if (q->unref)
			(*q->unref) (&q->what, MDL);
		q->next = free_timeouts;
		free_timeouts = q;
	}
}
