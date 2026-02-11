nm_gconf_get_bool_helper (GConfClient *client,
                          const char *path,
                          const char *key,
                          const char *setting,
                          gboolean *value)
{
	char *		gc_key;
	GConfValue *	gc_value;
	gboolean		success = FALSE;

	g_return_val_if_fail (key != NULL, FALSE);
	g_return_val_if_fail (setting != NULL, FALSE);
	g_return_val_if_fail (value != NULL, FALSE);

	gc_key = g_strdup_printf ("%s/%s/%s", path, setting, key);
	if ((gc_value = gconf_client_get (client, gc_key, NULL)))
	{
		if (gc_value->type == GCONF_VALUE_BOOL)
		{
			*value = gconf_value_get_bool (gc_value);
			success = TRUE;
		}
		else if (gc_value->type == GCONF_VALUE_STRING && !*gconf_value_get_string (gc_value))
		{

			*value = TRUE;
			success = TRUE;
		}

		gconf_value_free (gc_value);
	}
	g_free (gc_key);

	return success;
}
