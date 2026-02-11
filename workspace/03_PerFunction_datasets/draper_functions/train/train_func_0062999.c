NP_GetMIMEDescription (void)
{
	GString *list;

	if (mime_list != NULL)
		return mime_list;

	g_type_init ();

	list = g_string_new (NULL);


	GKeyFile *system, *user;

	system = g_key_file_new ();
	user = g_key_file_new ();

	if (g_key_file_load_from_file (system,
				       SYSCONFDIR"/totem/browser-plugins.ini",
				       G_KEY_FILE_NONE,
				       NULL) == FALSE) {
		g_key_file_free (system);
		system = NULL;
	}

	char *user_ini_file;
	user_ini_file = g_build_filename (g_get_user_config_dir (),
					  "totem",
					  "browser-plugins.ini",
					  NULL);
	if (g_key_file_load_from_file (user,
				       user_ini_file,
				       G_KEY_FILE_NONE,
				       NULL) == FALSE) {
		g_key_file_free (user);
		user = NULL;
	}
	g_free (user_ini_file);

	const totemPluginMimeEntry *mimetypes;
	uint32_t count;
	totemPlugin::PluginMimeTypes (&mimetypes, &count);
	for (uint32_t i = 0; i < count; ++i) {
		char *desc;

		if (totem_plugin_mimetype_is_disabled (mimetypes[i].mimetype, system, user))
			continue;

		desc = NULL;
		if (mimetypes[i].mime_alias != NULL) {
			if (strstr (mimetypes[i].mime_alias, "/") != NULL) {
				desc = g_content_type_get_description
					(mimetypes[i].mime_alias);
			} else {
				desc = g_strdup (mimetypes[i].mime_alias);
			}
		}

		if (desc == NULL)
			desc = g_content_type_get_description (mimetypes[i].mimetype);

		g_string_append_printf (list,"%s:%s:%s;",
					mimetypes[i].mimetype,
					mimetypes[i].extensions,
					desc);
		g_free (desc);
	}

	mime_list = g_string_free (list, FALSE);

	if (user != NULL)
		g_key_file_free (user);
	if (system != NULL)
		g_key_file_free (system);

	return mime_list;
}
