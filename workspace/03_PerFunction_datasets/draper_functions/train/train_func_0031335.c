event_base_priority_init(struct event_base *base, int npriorities)
{
	int i;

	if (N_ACTIVE_CALLBACKS(base) || npriorities < 1
	    || npriorities >= EVENT_MAX_PRIORITIES)
		return (-1);

	if (npriorities == base->nactivequeues)
		return (0);

	if (base->nactivequeues) {
		mm_free(base->activequeues);
		base->nactivequeues = 0;
	}


	base->activequeues = (struct event_list *)
	  mm_calloc(npriorities, sizeof(struct event_list));
	if (base->activequeues == NULL) {
		event_warn("%s: calloc", __func__);
		return (-1);
	}
	base->nactivequeues = npriorities;

	for (i = 0; i < base->nactivequeues; ++i) {
		TAILQ_INIT(&base->activequeues[i]);
	}

	return (0);
}
