test_read_with_schema (Test *test,
                       gconstpointer unused)
{
	GkmDataResult res;
	GkmSecret *master;
	GkmSecretItem *item;

	master = gkm_secret_new_from_password ("test");
	gkm_secret_data_set_master (test->sdata, master);
	g_object_unref (master);
	res = check_read_keyring_file (test, SRCDIR "/files/encrypted-with-schema.keyring");
	g_assert_cmpint (res, ==, GKM_DATA_SUCCESS);

	item = gkm_secret_collection_get_item (test->collection, "1");
	g_assert (item != NULL);

	g_assert_cmpstr (gkm_secret_item_get_schema (item), ==, "se.lostca.is.rishi.secret");
}
