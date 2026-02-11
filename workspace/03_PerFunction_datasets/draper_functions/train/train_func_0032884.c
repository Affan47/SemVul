gtk_hotkey_key_file_registry_real_get_application_hotkeys (GtkHotkeyRegistry	*base,
														 const char			*app_id,
														 GError				**error)
{
	GKeyFile					*keyfile;

	g_return_val_if_fail (app_id != NULL, NULL);

	keyfile = get_hotkey_key_file (app_id, error);

	if (keyfile == NULL)
		return NULL;

	return get_all_hotkey_infos_from_key_file (keyfile, app_id);
}
