gnome_online_accounts_ref_account (EGnomeOnlineAccounts *extension,
                                   ESource *source)
{
	ESourceRegistryServer *server;
	GoaObject *match = NULL;
	const gchar *extension_name;
	gchar *account_id = NULL;

	extension_name = E_SOURCE_EXTENSION_GOA;
	server = gnome_online_accounts_get_server (extension);

	source = e_source_registry_server_find_extension (
		server, source, extension_name);

	if (source != NULL) {
		ESourceGoa *goa_ext;

		goa_ext = e_source_get_extension (source, extension_name);
		account_id = e_source_goa_dup_account_id (goa_ext);

		g_object_unref (source);
	}

	if (account_id != NULL) {
		match = e_goa_client_lookup_by_id (
			extension->goa_client, account_id);
		g_free (account_id);
	}

	return match;
}
