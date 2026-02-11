event_unregister_action (EVENT ** head, EVENT * bad)
{
	EVENT *e;

	if (head == NULL)
		head = &evhead;

	for (e = *head; e->next; e = e->next) {
		if (e->next == bad) {
			while (bad->stack)
				event_unregister_action (&bad->stack,
							 bad->stack);

			e->next = bad->next;
			break;
		}
	}

	*head = bad->next;
	free (bad);
}
