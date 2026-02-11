pk_transaction_get_repo_list (PkTransaction *transaction,
			      GVariant *params,
			      GDBusMethodInvocation *context)
{
	gboolean ret;
	GError *error = NULL;
	PkBitfield filter;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);

	g_variant_get (params, "(t)",
		       &filter);

	g_debug ("GetRepoList method called");


	if (!pk_backend_is_implemented (transaction->priv->backend,
					PK_ROLE_ENUM_GET_REPO_LIST)) {
		error = g_error_new (PK_TRANSACTION_ERROR, PK_TRANSACTION_ERROR_NOT_SUPPORTED,
				     "GetRepoList not supported by backend");
		pk_transaction_release_tid (transaction);
		goto out;
	}


	transaction->priv->cached_filters = filter;
	pk_transaction_set_role (transaction, PK_ROLE_ENUM_GET_REPO_LIST);


	ret = pk_transaction_commit (transaction);
	if (!ret) {
		error = g_error_new (PK_TRANSACTION_ERROR,
				     PK_TRANSACTION_ERROR_COMMIT_FAILED,
				     "Could not commit to a transaction object");
		pk_transaction_release_tid (transaction);
		goto out;
	}
out:
	pk_transaction_dbus_return (context, error);
}
