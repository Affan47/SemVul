test_label_prop (Test *test, gconstpointer unused)
{
	const gchar *label;


	gboolean notified = FALSE;
	g_signal_connect (test->object, "notify::label", G_CALLBACK (was_notified), &notified);


	label = gkm_secret_object_get_label (test->object);
	g_assert_cmpstr (label, ==, "");


	gkm_secret_object_set_label (test->object, "hello");
	g_assert (notified);
	label = gkm_secret_object_get_label (test->object);
	g_assert_cmpstr (label, ==, "hello");
}
