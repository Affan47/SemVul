test_create_failed (Test *test, gconstpointer unused)
{
	GkmTransaction *transaction;
	GkmSecretItem *item;

	transaction = gkm_transaction_new ();
	item = gkm_secret_collection_create_item (test->collection, transaction);
	g_assert (GKM_IS_SECRET_ITEM (item));
	g_object_ref (item);
	g_assert (gkm_secret_collection_has_item (test->collection, item));

	gkm_transaction_fail (transaction, CKR_GENERAL_ERROR);
	gkm_transaction_complete (transaction);
	g_object_unref (transaction);


	g_assert (!gkm_secret_collection_has_item (test->collection, item));
	g_object_unref (item);
}
