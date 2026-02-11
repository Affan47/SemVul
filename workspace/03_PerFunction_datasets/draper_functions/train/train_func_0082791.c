window_bind_find(WINDOW_REC *window, const char *servertag,
				  const char *name)
{
	GSList *tmp;

        g_return_val_if_fail(window != NULL, NULL);
        g_return_val_if_fail(servertag != NULL, NULL);
        g_return_val_if_fail(name != NULL, NULL);

	for (tmp = window->bound_items; tmp != NULL; tmp = tmp->next) {
		WINDOW_BIND_REC *rec = tmp->data;

		if (g_strcasecmp(rec->name, name) == 0 &&
		    g_strcasecmp(rec->servertag, servertag) == 0)
                        return rec;
	}

        return NULL;
}
