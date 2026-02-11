yahoo_backend_child_added (ECollectionBackend *backend,
                           ESource *child_source)
{
	EYahooBackend *yahoo_backend;
	ESource *collection_source;
	const gchar *extension_name;
	gboolean is_mail = FALSE;

	yahoo_backend = E_YAHOO_BACKEND (backend);
	collection_source = e_backend_get_source (E_BACKEND (backend));

	extension_name = E_SOURCE_EXTENSION_MAIL_ACCOUNT;
	is_mail |= e_source_has_extension (child_source, extension_name);


	extension_name = E_SOURCE_EXTENSION_MAIL_IDENTITY;
	if (e_source_has_extension (child_source, extension_name)) {
		GWeakRef *weak_ref;

		weak_ref = &yahoo_backend->mail_identity_source;
		g_weak_ref_set (weak_ref, child_source);
		is_mail = TRUE;
	}

	extension_name = E_SOURCE_EXTENSION_MAIL_TRANSPORT;
	is_mail |= e_source_has_extension (child_source, extension_name);


	extension_name = E_SOURCE_EXTENSION_AUTHENTICATION;
	if (is_mail && e_source_has_extension (child_source, extension_name)) {
		ESourceAuthentication *auth_child_extension;
		ESourceCollection *collection_extension;
		const gchar *collection_identity;
		const gchar *auth_child_user;

		extension_name = E_SOURCE_EXTENSION_COLLECTION;
		collection_extension = e_source_get_extension (
			collection_source, extension_name);
		collection_identity = e_source_collection_get_identity (
			collection_extension);

		extension_name = E_SOURCE_EXTENSION_AUTHENTICATION;
		auth_child_extension = e_source_get_extension (
			child_source, extension_name);
		auth_child_user = e_source_authentication_get_user (
			auth_child_extension);


		if (auth_child_user == NULL)
			e_source_authentication_set_user (
				auth_child_extension,
				collection_identity);
	}


	E_COLLECTION_BACKEND_CLASS (e_yahoo_backend_parent_class)->
		child_added (backend, child_source);
}
