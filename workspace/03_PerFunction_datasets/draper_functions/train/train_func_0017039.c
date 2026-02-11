test_serialize (void)
{
  TestObject *obj = g_object_new (TEST_TYPE_OBJECT, "bar", TRUE, NULL);
  gchar *data;
  gsize len;

  data = json_gobject_to_data (G_OBJECT (obj), &len);

  g_assert (data != NULL);
  g_assert_cmpint (len, >, 0);
  g_assert_cmpint (len, ==, strlen (data));

  if (g_test_verbose ())
    g_print ("TestObject:\n%s\n", data);

  g_free (data);
  g_object_unref (obj);
}
