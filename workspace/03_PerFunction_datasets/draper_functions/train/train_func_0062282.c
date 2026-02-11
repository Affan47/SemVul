pk_transaction_list_set_background (PkTransactionList *tlist, const gchar *tid, gboolean background)
{
	PkTransactionItem *item;

	g_return_val_if_fail (PK_IS_TRANSACTION_LIST (tlist), FALSE);
	g_return_val_if_fail (tid != NULL, FALSE);

	item = pk_transaction_list_get_from_tid (tlist, tid);
	if (item == NULL) {
		g_warning ("could not get item");
		return FALSE;
	}
	if (pk_transaction_get_state (item->transaction) == PK_TRANSACTION_STATE_FINISHED) {
		g_debug ("already finished, so waiting to timeout");
		return FALSE;
	}
	g_debug ("%s is now background: %i", tid, background);
	item->background = background;
	return TRUE;
}
