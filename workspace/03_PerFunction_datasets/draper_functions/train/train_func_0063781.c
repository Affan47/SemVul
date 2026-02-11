ubuntu_online_accounts_config_mail_transport (EUbuntuOnlineAccounts *extension,
                                              ESource *source,
                                              GHashTable *account_services,
                                              const gchar *smtp_user_name)
{
	EServerSideSource *server_side_source;

	ubuntu_online_accounts_config_oauth2 (
		extension, source, account_services);

	if (smtp_user_name != NULL) {
		ESourceAuthentication *source_extension;

		source_extension = e_source_get_extension (
			source, E_SOURCE_EXTENSION_AUTHENTICATION);
		e_source_authentication_set_user (
			source_extension, smtp_user_name);
	}


	server_side_source = E_SERVER_SIDE_SOURCE (source);
	e_server_side_source_set_writable (server_side_source, TRUE);
	e_server_side_source_set_removable (server_side_source, FALSE);
}
