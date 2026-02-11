evsched_schedule(evsched_t *s, event_t *ev, uint32_t dt)
{
	if (!s || !ev) {
		return KNOT_EINVAL;
	}


	evsched_settimer(ev, dt);
	ev->parent = s;


	pthread_mutex_lock(&s->mx);

	heap_insert(&s->heap, ev);


	pthread_cond_broadcast(&s->notify);
	pthread_mutex_unlock(&s->mx);

	return KNOT_EOK;
}
