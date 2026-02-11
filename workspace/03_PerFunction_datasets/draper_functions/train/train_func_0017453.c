enchant_session_new (EnchantProvider *provider, const char * const lang)
{
	EnchantSession * session = NULL;
	GSList *user_config_dirs, *iter;

	user_config_dirs = enchant_get_user_config_dirs ();
	for (iter = user_config_dirs; iter != NULL && session == NULL; iter = iter->next)
		{
			session =_enchant_session_new (provider, iter->data, lang, TRUE);
		}

	if (session == NULL && user_config_dirs != NULL)
		{
			_enchant_ensure_dir_exists (user_config_dirs->data);

			session =_enchant_session_new (provider, user_config_dirs->data, lang, FALSE);
		}

	g_slist_foreach (user_config_dirs, (GFunc)g_free, NULL);
	g_slist_free (user_config_dirs);


	return session;
}
