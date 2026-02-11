dcc_unregister_type(const char *type)
{
	GSList *pos;

	pos = gslist_find_string(dcc_types, type);
	if (pos != NULL) {
		g_free(pos->data);
                dcc_types = g_slist_remove(dcc_types, pos->data);
	}
}
