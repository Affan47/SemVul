window_bind_remove_unsticky(WINDOW_REC *window)
{
	GSList *tmp, *next;

	for (tmp = window->bound_items; tmp != NULL; tmp = next) {
		WINDOW_BIND_REC *rec = tmp->data;

		next = tmp->next;
		if (!rec->sticky)
                        window_bind_destroy(window, rec);
	}
}
