e_authentication_session_store_password_sync (EAuthenticationSession *session,
                                              const gchar *password,
                                              gboolean permanently,
                                              GCancellable *cancellable,
                                              GError **error)
{
	gboolean result;
	const gchar *collection;
	const gchar *uid;
	gchar *display_name;

	g_return_val_if_fail (E_IS_AUTHENTICATION_SESSION (session), FALSE);
	g_return_val_if_fail (password != NULL, FALSE);

	if (permanently)
		collection = SECRET_COLLECTION_DEFAULT;
	else
		collection = SECRET_COLLECTION_SESSION;

	uid = e_authentication_session_get_source_uid (session);
	display_name = g_strdup_printf (KEYRING_ITEM_DISPLAY_FORMAT, uid);

	result = secret_password_store_sync (
		&schema, collection, display_name,
		password, cancellable, error,
		KEYRING_ITEM_ATTRIBUTE_NAME, uid,
		NULL);

	g_free (display_name);

	return result;
}
