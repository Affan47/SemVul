technology_save(struct connman_technology *technology)
{
	GKeyFile *keyfile;
	gchar *identifier;

	DBG("technology %p", technology);

	keyfile = __connman_storage_load_global();
	if (keyfile == NULL)
		keyfile = g_key_file_new();

	identifier = g_strdup_printf("%s", get_name(technology->type));
	if (identifier == NULL)
		goto done;

	g_key_file_set_boolean(keyfile, identifier, "Enable",
				technology->enable_persistent);

	g_key_file_set_boolean(keyfile, identifier, "Tethering",
				technology->tethering_persistent);

	if (technology->tethering_ident != NULL)
		g_key_file_set_string(keyfile, identifier,
					"Tethering.Identifier",
					technology->tethering_ident);

	if (technology->tethering_passphrase != NULL)
		g_key_file_set_string(keyfile, identifier,
					"Tethering.Passphrase",
					technology->tethering_passphrase);

done:
	g_free(identifier);

	__connman_storage_save_global(keyfile);

	g_key_file_free(keyfile);

	return;
}
