pk_transaction_get_requires (PkTransaction *transaction,
			     GVariant *params,
			     GDBusMethodInvocation *context)
{
	gboolean ret;
	GError *error = NULL;
	gchar *package_ids_temp;
	guint length;
	guint max_length;
	PkBitfield filter;
	gchar **package_ids;
	gboolean recursive;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);

	g_variant_get (params, "(t^a&sb)",
		       &filter,
		       &package_ids,
		       &recursive);

	package_ids_temp = pk_package_ids_to_string (package_ids);
	g_debug ("GetRequires method called: %s (recursive %i)", package_ids_temp, recursive);


	if (!pk_backend_is_implemented (transaction->priv->backend,
					PK_ROLE_ENUM_GET_REQUIRES)) {
		error = g_error_new (PK_TRANSACTION_ERROR, PK_TRANSACTION_ERROR_NOT_SUPPORTED,
				     "GetRequires not supported by backend");
		pk_transaction_release_tid (transaction);
		goto out;
	}


	length = g_strv_length (package_ids);
	max_length = pk_conf_get_int (transaction->priv->conf, "MaximumPackagesToProcess");
	if (length > max_length) {
		error = g_error_new (PK_TRANSACTION_ERROR, PK_TRANSACTION_ERROR_NUMBER_OF_PACKAGES_INVALID,
				     "Too many packages to process (%i/%i)", length, max_length);
		pk_transaction_release_tid (transaction);
		goto out;
	}


	ret = pk_package_ids_check (package_ids);
	if (!ret) {
		error = g_error_new (PK_TRANSACTION_ERROR, PK_TRANSACTION_ERROR_PACKAGE_ID_INVALID,
				     "The package id's '%s' are not valid", package_ids_temp);
		pk_transaction_release_tid (transaction);
		goto out;
	}


	transaction->priv->cached_filters = filter;
	transaction->priv->cached_package_ids = g_strdupv (package_ids);
	transaction->priv->cached_force = recursive;
	pk_transaction_set_role (transaction, PK_ROLE_ENUM_GET_REQUIRES);


	ret = pk_transaction_commit (transaction);
	if (!ret) {
		error = g_error_new (PK_TRANSACTION_ERROR, PK_TRANSACTION_ERROR_COMMIT_FAILED,
				     "Could not commit to a transaction object");
		pk_transaction_release_tid (transaction);
		goto out;
	}
out:
	g_free (package_ids_temp);
	pk_transaction_dbus_return (context, error);
}
