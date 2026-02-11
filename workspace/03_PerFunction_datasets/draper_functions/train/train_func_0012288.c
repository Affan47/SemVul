pk_engine_transaction_list_changed_cb (PkTransactionList *tlist, PkEngine *engine)
{
	gchar **transaction_list;
	gboolean locked;

	g_return_if_fail (PK_IS_ENGINE (engine));


	locked = pk_transaction_list_get_locked (tlist);
	pk_engine_set_locked (engine, locked);

	g_debug ("emitting transaction-list-changed");
	transaction_list = pk_transaction_list_get_array (engine->priv->transaction_list);
	g_dbus_connection_emit_signal (engine->priv->connection,
				       NULL,
				       PK_DBUS_PATH,
				       PK_DBUS_INTERFACE,
				       "TransactionListChanged",
				       g_variant_new ("(^a&s)",
						      transaction_list),
				       NULL);
	pk_engine_reset_timer (engine);

	g_strfreev (transaction_list);
}
