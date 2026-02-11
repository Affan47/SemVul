gda_connection_internal_savepoint_added (GdaConnection *cnc, const gchar *parent_trans, const gchar *svp_name)
{
	GdaTransactionStatus *st;

	g_return_if_fail (GDA_IS_CONNECTION (cnc));

	gda_connection_lock ((GdaLockable*) cnc);

	st = gda_transaction_status_find (cnc->priv->trans_status, parent_trans, NULL);
	if (st) {
		gda_transaction_status_add_event_svp (st, svp_name);
#ifdef GDA_DEBUG_signal
		g_print (">> 'TRANSACTION_STATUS_CHANGED' from %s\n", __FUNCTION__);
#endif
		g_signal_emit (G_OBJECT (cnc), gda_connection_signals[TRANSACTION_STATUS_CHANGED], 0);
#ifdef GDA_DEBUG_signal
		g_print ("<< 'TRANSACTION_STATUS_CHANGED' from %s\n", __FUNCTION__);
#endif
	}
	else {
		g_warning (_("Connection transaction status tracking: no transaction exists for %s"), "ADD SAVEPOINT");
	}
#ifdef GDA_DEBUG_NO
	if (cnc->priv->trans_status)
		gda_transaction_status_dump (cnc->priv->trans_status, 5);
#endif

	gda_connection_unlock ((GdaLockable*) cnc);
}
