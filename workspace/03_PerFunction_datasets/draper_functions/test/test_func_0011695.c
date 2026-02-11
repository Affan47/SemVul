pk_client_fixup_dbus_error (GError *error)
{
	gchar *name = NULL;
	const gchar *name_suffix = NULL;

	g_return_if_fail (error != NULL);


	if (g_str_has_prefix (error->message, "org.freedesktop.packagekit.")) {
		g_debug ("fixing up code for Policykit auth failure");
		error->code = PK_CLIENT_ERROR_FAILED_AUTH;
		g_free (error->message);
		error->message = g_strdup ("PolicyKit authorization failure");
		goto out;
	}


	if (!g_dbus_error_is_remote_error (error))
		goto out;


	error->domain = PK_CLIENT_ERROR;
	error->code = PK_CLIENT_ERROR_FAILED;


	name = g_dbus_error_get_remote_error (error);
	g_dbus_error_strip_remote_error (error);
	if (g_str_has_prefix (name, "org.freedesktop.PackageKit.Transaction."))
		name_suffix = &name[39];
	if (g_strcmp0 (name_suffix, "Denied") == 0 ||
	    g_strcmp0 (name_suffix, "RefusedByPolicy") == 0) {
		error->code = PK_CLIENT_ERROR_FAILED_AUTH;
		goto out;
	}
	if (g_strcmp0 (name_suffix, "PackageIdInvalid") == 0 ||
		 g_strcmp0 (name_suffix, "SearchInvalid") == 0 ||
		 g_strcmp0 (name_suffix, "FilterInvalid") == 0 ||
		 g_strcmp0 (name_suffix, "InvalidProvide") == 0 ||
		 g_strcmp0 (name_suffix, "InputInvalid") == 0) {
		error->code = PK_CLIENT_ERROR_INVALID_INPUT;
		goto out;
	}
	if (g_strcmp0 (name_suffix, "PackInvalid") == 0 ||
	    g_strcmp0 (name_suffix, "NoSuchFile") == 0 ||
	    g_strcmp0 (name_suffix, "MimeTypeNotSupported") == 0 ||
	    g_strcmp0 (name_suffix, "NoSuchDirectory") == 0) {
		error->code = PK_CLIENT_ERROR_INVALID_FILE;
		goto out;
	}
	if (g_strcmp0 (name_suffix, "NotSupported") == 0) {
		error->code = PK_CLIENT_ERROR_NOT_SUPPORTED;
		goto out;
	}
	g_warning ("couldn't parse execption '%s', please report", name);
out:
	g_free (name);
}
