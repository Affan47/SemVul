transport_prio_sendqs_empty(void)
{
	struct transport *t;

	for (t = LIST_FIRST(&transport_list); t; t = LIST_NEXT(t, link))
		if (TAILQ_FIRST(&t->virtual->prio_sendq))
			return 0;
	return 1;
}
