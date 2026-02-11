nm_gconf_set_bytearray_helper (GConfClient *client,
                               const char *path,
                               const char *key,
                               const char *setting,
                               GByteArray *value)
{
	char *gc_key;
	int i;
	GSList *list = NULL;

	g_return_val_if_fail (path != NULL, FALSE);
	g_return_val_if_fail (key != NULL, FALSE);
	g_return_val_if_fail (setting != NULL, FALSE);

	if (!value)
		return TRUE;

	gc_key = g_strdup_printf ("%s/%s/%s", path, setting, key);
	if (!gc_key) {
		g_warning ("Not enough memory to create gconf path");
		return FALSE;
	}

	for (i = 0; i < value->len; i++)
		list = g_slist_append(list, GINT_TO_POINTER ((int) value->data[i]));

	gconf_client_set_list (client, gc_key, GCONF_VALUE_INT, list, NULL);

	g_slist_free (list);
	g_free (gc_key);
	return TRUE;
}
