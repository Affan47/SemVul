prefs_set_config_val_real (char *key, char *value, gboolean callback)
{
	ConfigVar *entry = prefs_config_vars;
	while (entry->key)
	{
		if (strcasecmp (entry->key, key) == 0)
		{

			entry->cur_val = g_strdup (value);
			if (callback && entry->callback)
				entry->callback (key, value);
			return;
		}
		entry++;
	}
	fprintf (stderr, "Warning: invalid key %s in config file\n", key);
}
