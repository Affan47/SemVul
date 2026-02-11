test_label_set_attr (Test *test, gconstpointer unused)
{
	CK_ATTRIBUTE attr = { CKA_LABEL, "hello", 5 };
	GkmTransaction *transaction = gkm_transaction_new ();


	gboolean notified = FALSE;
	g_signal_connect (test->object, "notify::label", G_CALLBACK (was_notified), &notified);

	gkm_object_set_attribute (GKM_OBJECT (test->object), test->session, transaction, &attr);
	g_assert (!gkm_transaction_get_failed (transaction));
	g_assert (!notified);

	g_assert_cmpstr (gkm_secret_object_get_label (test->object), ==, "hello");

	gkm_transaction_complete (transaction);
	g_assert_cmpstr (gkm_secret_object_get_label (test->object), ==, "hello");
	g_assert (notified);

	g_object_unref (transaction);
}
