pk_transaction_get_property (GDBusConnection *connection_, const gchar *sender,
			     const gchar *object_path, const gchar *interface_name,
			     const gchar *property_name, GError **error,
			     gpointer user_data)
{
	GVariant *retval = NULL;
	PkTransaction *transaction = PK_TRANSACTION (user_data);
	PkTransactionPrivate *priv = transaction->priv;

	if (g_strcmp0 (property_name, "Role") == 0) {
		retval = g_variant_new_uint32 (priv->role);
		goto out;
	}
	if (g_strcmp0 (property_name, "Status") == 0) {
		retval = g_variant_new_uint32 (priv->status);
		goto out;
	}
	if (g_strcmp0 (property_name, "LastPackage") == 0) {
		retval = _g_variant_new_maybe_string (priv->last_package_id);
		goto out;
	}
	if (g_strcmp0 (property_name, "Uid") == 0) {
		retval = g_variant_new_uint32 (priv->uid);
		goto out;
	}
	if (g_strcmp0 (property_name, "Percentage") == 0) {
		retval = g_variant_new_uint32 (transaction->priv->percentage);
		goto out;
	}
	if (g_strcmp0 (property_name, "AllowCancel") == 0) {
		retval = g_variant_new_boolean (priv->allow_cancel);
		goto out;
	}
	if (g_strcmp0 (property_name, "CallerActive") == 0) {
		retval = g_variant_new_boolean (priv->caller_active);
		goto out;
	}
	if (g_strcmp0 (property_name, "ElapsedTime") == 0) {
		retval = g_variant_new_uint32 (priv->elapsed_time);
		goto out;
	}
	if (g_strcmp0 (property_name, "RemainingTime") == 0) {
		retval = g_variant_new_uint32 (priv->remaining_time);
		goto out;
	}
	if (g_strcmp0 (property_name, "Speed") == 0) {
		retval = g_variant_new_uint32 (priv->speed);
		goto out;
	}
	if (g_strcmp0 (property_name, "DownloadSizeRemaining") == 0) {
		retval = g_variant_new_uint64 (priv->download_size_remaining);
		goto out;
	}
	if (g_strcmp0 (property_name, "TransactionFlags") == 0) {
		retval = g_variant_new_uint64 (priv->cached_transaction_flags);
		goto out;
	}
out:
	return retval;
}
