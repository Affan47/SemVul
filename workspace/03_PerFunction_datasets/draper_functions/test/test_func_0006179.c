window_bind_add(WINDOW_REC *window, const char *servertag,
				 const char *name)
{
	WINDOW_BIND_REC *rec;

        g_return_val_if_fail(window != NULL, NULL);
        g_return_val_if_fail(servertag != NULL, NULL);
	g_return_val_if_fail(name != NULL, NULL);

	rec = window_bind_find(window, servertag, name);
	if (rec != NULL)
		return rec;

	rec = g_new0(WINDOW_BIND_REC, 1);
        rec->name = g_strdup(name);
        rec->servertag = g_strdup(servertag);

	window->bound_items = g_slist_append(window->bound_items, rec);
        return rec;
}
