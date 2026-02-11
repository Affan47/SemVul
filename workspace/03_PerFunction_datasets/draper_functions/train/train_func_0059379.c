test_destroy_failed (Test *test, gconstpointer unused)
{
	GkmTransaction *transaction;
	GkmSecretItem *item;

	item = gkm_secret_collection_new_item (test->collection, "the-identifier");
	g_assert (gkm_secret_collection_has_item (test->collection, item));
	g_object_ref (item);

	transaction = gkm_transaction_new ();
	gkm_secret_collection_destroy_item (test->collection, transaction, item);
	g_assert (!gkm_secret_collection_has_item (test->collection, item));

	gkm_transaction_fail (transaction, CKR_GENERAL_ERROR);
	gkm_transaction_complete (transaction);
	g_object_unref (transaction);


	g_assert (gkm_secret_collection_has_item (test->collection, item));
	g_object_unref (item);
}
