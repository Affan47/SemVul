secret_service_read_alias_dbus_path_finish (SecretService *self,
                                            GAsyncResult *result,
                                            GError **error)
{
	gchar *collection_path;
	GVariant *retval;

	retval = g_dbus_proxy_call_finish (G_DBUS_PROXY (self), result, error);

	_secret_util_strip_remote_error (error);
	if (retval == NULL)
		return NULL;

	g_variant_get (retval, "(o)", &collection_path);
	g_variant_unref (retval);

	if (g_str_equal (collection_path, "/")) {
		g_free (collection_path);
		collection_path = NULL;
	}

	return collection_path;
}
