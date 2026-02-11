midgard_config_read_file_at_path(MidgardConfig *self, const gchar *filepath, GError **error)
{
	g_assert (self != NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

	GKeyFile *keyfile = NULL;

	if (filepath == NULL || *filepath == '\0') {

			g_set_error (error, MGD_GENERIC_ERROR, MGD_ERR_INVALID_NAME, "Configuration file path can not be empty");

		return FALSE;
	}

	GError *kf_error = NULL;
	keyfile = g_key_file_new();

	if (!g_key_file_load_from_file(keyfile, filepath, G_KEY_FILE_NONE, &kf_error)) {

		g_set_error (error, MGD_GENERIC_ERROR, MGD_ERR_INTERNAL, "Can not open %s. %s" , filepath, kf_error->message);

		g_clear_error(&kf_error);
		return FALSE;
	}

	__set_config_from_keyfile(self, keyfile, filepath);

	return TRUE;
}
