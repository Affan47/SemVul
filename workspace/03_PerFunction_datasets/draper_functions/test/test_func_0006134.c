pk_transaction_list_get_array (PkTransactionList *tlist)
{
	guint i;
	guint length;
	GPtrArray *parray;
	gchar **array;
	PkTransactionItem *item;
	PkTransactionState state;

	g_return_val_if_fail (PK_IS_TRANSACTION_LIST (tlist), NULL);


	parray = g_ptr_array_new_with_free_func (g_free);


	length = tlist->priv->array->len;
	for (i = 0; i < length; i++) {
		item = (PkTransactionItem *) g_ptr_array_index (tlist->priv->array, i);

		state = pk_transaction_get_state (item->transaction);
		if (state == PK_TRANSACTION_STATE_COMMITTED ||
		    state == PK_TRANSACTION_STATE_READY ||
		    state == PK_TRANSACTION_STATE_RUNNING)
			g_ptr_array_add (parray, g_strdup (item->tid));
	}
	g_debug ("%i transactions in list, %i committed but not finished", length, parray->len);
	array = pk_ptr_array_to_strv (parray);
	g_ptr_array_unref (parray);

	return array;
}
