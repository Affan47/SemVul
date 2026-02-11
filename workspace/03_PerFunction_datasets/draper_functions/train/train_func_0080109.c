test_unique_file_conflict_with_ext (Test* test, gconstpointer unused)
{
	GkmTransaction *transaction = gkm_transaction_new ();
	const gchar *filename = "/tmp/transaction-test.ext";
	gchar *dirname;
	gchar *basename;
	gchar *result;

	dirname = g_path_get_dirname (filename);
	basename = g_path_get_basename (filename);

	g_assert (g_file_set_contents (filename, "data", -1, NULL));

	result = gkm_transaction_unique_file (transaction, dirname, basename);
	g_assert (!gkm_transaction_get_failed (transaction));

	g_assert (result);
	g_assert_cmpstr (result, !=, basename);
	g_assert_cmpstr (result, ==, "transaction-test_1.ext");

	g_free (dirname);
	g_free (basename);
	g_free (result);

	g_object_unref (transaction);
}
