remove_item (GkmSecretCollection *self, GkmTransaction *transaction, GkmSecretItem *item)
{
	const gchar *identifier;

	g_assert (GKM_IS_SECRET_COLLECTION (self));
	g_assert (GKM_IS_SECRET_ITEM (item));

	identifier = gkm_secret_object_get_identifier (GKM_SECRET_OBJECT (item));
	g_return_if_fail (identifier);

	g_object_ref (item);

	g_hash_table_remove (self->items, identifier);

	gkm_object_expose_full (GKM_OBJECT (item), transaction, FALSE);
	if (transaction)
		gkm_transaction_add (transaction, self, (GkmTransactionFunc)complete_remove,
		                     g_object_ref (item));

	g_object_unref (item);
}
