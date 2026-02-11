filetypes_load_config(guint ft_id, gboolean reload)
{
	GKeyFile *config, *config_home;
	GeanyFiletypePrivate *pft;
	GeanyFiletype *ft;

	g_return_if_fail(ft_id < filetypes_array->len);

	ft = filetypes[ft_id];
	pft = ft->priv;


	if (G_UNLIKELY(reload && ! pft->keyfile_loaded))
		return;


	if (G_LIKELY(! reload && pft->keyfile_loaded))
		return;
	pft->keyfile_loaded = TRUE;

	config = g_key_file_new();
	config_home = g_key_file_new();
	{

		gchar *f;

		f = filetypes_get_filename(ft, FALSE);
		load_system_keyfile(config, f, G_KEY_FILE_KEEP_COMMENTS, ft);

		SETPTR(f, filetypes_get_filename(ft, TRUE));
		g_key_file_load_from_file(config_home, f, G_KEY_FILE_KEEP_COMMENTS, NULL);
		g_free(f);
	}

	copy_ft_groups(config);
	copy_ft_groups(config_home);

	load_settings(ft_id, config, config_home);
	highlighting_init_styles(ft_id, config, config_home);

	g_key_file_free(config);
	g_key_file_free(config_home);
}
