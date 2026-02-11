get_secrets_cb (NMRemoteConnection *connection,
                GHashTable *secrets,
                GError *error,
                gpointer user_data)
{
	GetSecretsInfo *info = user_data;
	NMAWifiDialogPrivate *priv;
	GHashTableIter hash_iter;
	gpointer key, value;
	GtkTreeModel *model;
	GtkTreeIter iter;

	if (info->canceled)
		goto out;

	priv = NMA_WIFI_DIALOG_GET_PRIVATE (info->self);
	if (priv->secrets_info == info) {
		priv->secrets_info = NULL;


		gtk_dialog_set_response_sensitive (GTK_DIALOG (info->self), GTK_RESPONSE_CANCEL, TRUE);
		gtk_dialog_set_response_sensitive (GTK_DIALOG (info->self), GTK_RESPONSE_OK, TRUE);
	}

	if (error) {
		g_warning ("%s: error getting connection secrets: (%d) %s",
		           __func__,
		           error ? error->code : -1,
		           error && error->message ? error->message : "(unknown)");
		goto out;
	}


	if (   (priv->connection != info->connection)
	    || !secrets
	    || !g_hash_table_size (secrets))
		goto out;


	g_hash_table_iter_init (&hash_iter, secrets);
	while (g_hash_table_iter_next (&hash_iter, &key, &value)) {
		GError *update_error = NULL;
		const char *setting_name = key;
		GHashTable *setting_hash = value;

		if (!nm_connection_update_secrets (priv->connection,
		                                   setting_name,
		                                   setting_hash,
		                                   &update_error)) {
			g_warning ("%s: error updating connection secrets: (%d) %s",
			           __func__,
			           update_error ? update_error->code : -1,
			           update_error && update_error->message ? update_error->message : "(unknown)");
			g_clear_error (&update_error);
		}
	}


	model = gtk_combo_box_get_model (GTK_COMBO_BOX (priv->sec_combo));
	if (gtk_tree_model_get_iter_first (model, &iter)) {
		do {
			WirelessSecurity *sec = NULL;

			gtk_tree_model_get (model, &iter, S_SEC_COLUMN, &sec, -1);
			if (sec) {
				wireless_security_update_secrets (sec, priv->connection);
				wireless_security_unref (sec);
			}
		} while (gtk_tree_model_iter_next (model, &iter));
	}

out:
	g_object_unref (info->connection);
	g_free (info);
}
