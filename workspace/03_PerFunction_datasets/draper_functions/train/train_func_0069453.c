pk_transaction_get_categories (PkTransaction *transaction,
			       GVariant *params,
			       GDBusMethodInvocation *context)
{
	gboolean ret;
	GError *error = NULL;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);

	g_debug ("GetCategories method called");


	if (!pk_backend_is_implemented (transaction->priv->backend,
					PK_ROLE_ENUM_GET_CATEGORIES)) {
		error = g_error_new (PK_TRANSACTION_ERROR, PK_TRANSACTION_ERROR_NOT_SUPPORTED,
				     "GetCategories not supported by backend");
		pk_transaction_release_tid (transaction);
		goto out;
	}

	pk_transaction_set_role (transaction, PK_ROLE_ENUM_GET_CATEGORIES);


	ret = pk_transaction_commit (transaction);
	if (!ret) {
		error = g_error_new (PK_TRANSACTION_ERROR, PK_TRANSACTION_ERROR_COMMIT_FAILED,
				     "Could not commit to a transaction object");
		pk_transaction_release_tid (transaction);
		goto out;
	}
out:
	pk_transaction_dbus_return (context, error);
}
