spell_notify_languages_cb (GSettings   *gsettings,
			   const gchar *key,
			   gpointer     user_data)
{
	DEBUG ("Resetting languages due to config change");


	if (languages != NULL) {
		g_hash_table_unref (languages);
		languages = NULL;
	}
}
