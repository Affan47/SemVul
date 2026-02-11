window_item_next(WINDOW_REC *window)
{
	WI_ITEM_REC *next;
	GSList *tmp;
	int gone;

	g_return_if_fail(window != NULL);

	next = NULL; gone = FALSE;
	for (tmp = window->items; tmp != NULL; tmp = tmp->next) {
		WI_ITEM_REC *rec = tmp->data;

		if (rec == window->active)
			gone = TRUE;
		else {
			if (gone) {

				next = rec;
				break;
			}

			if (next == NULL)
				next = rec;
		}
	}

	if (next != NULL)
                window_item_set_active(window, next);
}
