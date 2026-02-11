pk_transaction_list_remove_internal (PkTransactionList *tlist, PkTransactionItem *item)
{
	gboolean ret;

	g_return_val_if_fail (PK_IS_TRANSACTION_LIST (tlist), FALSE);
	g_return_val_if_fail (item != NULL, FALSE);


	g_debug ("remove transaction %s, item %p", item->tid, item);
	ret = g_ptr_array_remove (tlist->priv->array, item);
	if (!ret) {
		g_warning ("could not remove %p as not present in list", item);
		return FALSE;
	}
	pk_transaction_list_item_free (item);

	return TRUE;
}
