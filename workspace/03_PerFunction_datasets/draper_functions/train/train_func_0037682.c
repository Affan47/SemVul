setup_fixture (ETestServerFixture *fixture,
               gconstpointer user_data)
{
	GError *error = NULL;
	ESource *scratch;
	ESourceMailAccount *mail_account;
	ESourceMailIdentity *mail_identity;

	e_test_server_utils_setup (fixture, user_data);


	scratch = e_source_new_with_uid (MAIL_IDENTITY_UID, NULL, &error);
	if (!scratch)
		g_error ("Failed to create scratch source for an email user: %s", error->message);

	mail_identity = e_source_get_extension (scratch, E_SOURCE_EXTENSION_MAIL_IDENTITY);
	e_source_mail_identity_set_address (mail_identity, USER_EMAIL);

	if (!e_source_registry_commit_source_sync (fixture->registry, scratch, NULL, &error))
		g_error ("Unable to add new addressbook source to the registry: %s", error->message);

	g_object_unref (scratch);


	scratch = e_source_new_with_uid (MAIL_ACCOUNT_UID, NULL, &error);
	if (!scratch)
		g_error ("Failed to create scratch source for an email user: %s", error->message);

	mail_account = e_source_get_extension (scratch, E_SOURCE_EXTENSION_MAIL_ACCOUNT);
	e_source_mail_account_set_identity_uid (mail_account, MAIL_IDENTITY_UID);

	if (!e_source_registry_commit_source_sync (fixture->registry, scratch, NULL, &error))
		g_error ("Unable to add new addressbook source to the registry: %s", error->message);

	g_object_unref (scratch);
}
