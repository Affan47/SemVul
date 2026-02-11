evsched_schedule_term(evsched_t *s, uint32_t dt)
{
	if (!s) {
		return NULL;
	}


	event_t *e = evsched_event_new(s, EVSCHED_TERM);
	if (!e) {
		return NULL;
	}


	if (evsched_schedule(s, e, dt) != 0) {
		evsched_event_free(s, e);
		e = NULL;
	}

	return e;
}
