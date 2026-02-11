do_test_write_file (Test* test)
{
	GkmTransaction *transaction = gkm_transaction_new ();
	const gchar *filename = "/tmp/transaction-test";
	gchar *data;
	gsize n_data;

	gkm_transaction_write_file (transaction, filename, (const guchar*)"value", 5);
	g_assert (!gkm_transaction_get_failed (transaction));

	g_assert (g_file_get_contents (filename, &data, &n_data, NULL));
	g_assert_cmpuint (n_data, ==, 5);
	g_assert_cmpstr (data, ==, "value");
	g_free (data);

	gkm_transaction_complete (transaction);

	g_assert (g_file_get_contents (filename, &data, &n_data, NULL));
	g_assert_cmpuint (n_data, ==, 5);
	g_assert_cmpstr (data, ==, "value");
	g_free (data);

	g_object_unref (transaction);
}
