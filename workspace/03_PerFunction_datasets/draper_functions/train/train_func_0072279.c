nautilus_keyfile_metadata_set_stringv (NautilusFile *file,
                                       const char *keyfile_filename,
                                       const char *name,
                                       const char *key,
                                       const char * const *stringv)
{
	GKeyFile *keyfile;
	guint length;
	gchar **actual_stringv = NULL;
	gboolean free_strv = FALSE;

	keyfile = get_keyfile (keyfile_filename);


	length = g_strv_length ((gchar **) stringv);

	if (length == 1) {
		actual_stringv = g_malloc0 (3 * sizeof (gchar *));
		actual_stringv[0] = (gchar *) stringv[0];
		actual_stringv[1] = STRV_TERMINATOR;
		actual_stringv[2] = NULL;

		length = 2;
		free_strv = TRUE;
	} else {
		actual_stringv = (gchar **) stringv;
	}

	g_key_file_set_string_list (keyfile,
	                            name,
	                            key,
	                            (const gchar **) actual_stringv,
	                            length);

	save_in_idle (keyfile_filename);

	if (nautilus_keyfile_metadata_update_from_keyfile (file, keyfile_filename, name)) {
		nautilus_file_changed (file);
	}

	if (free_strv) {
		g_free (actual_stringv);
	}
}
