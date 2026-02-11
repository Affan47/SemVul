complete_matches_found(const gchar *str)
{
	GList *result = NULL;
	gchar *d = NULL;

	cm_return_val_if_fail(str != NULL, 0);


	d = g_utf8_strdown(str, -1);

	clear_completion_cache();
	g_completion_prefix = g_strdup(str);

	result = g_completion_complete(g_completion, d, NULL);

	g_free(g_completion_prefix);
	g_free(d);

	return g_list_length(result);
}
