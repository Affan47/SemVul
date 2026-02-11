test_serialize_boxed (void)
{
  TestBoxed boxed = { 42, TRUE };
  GObject *obj;
  gchar *data;
  gsize len;

  obj = g_object_new (TEST_TYPE_OBJECT, "blah", &boxed, NULL);

  data = json_gobject_to_data (obj, &len);

  g_assert_cmpint (len, ==, strlen (serialize_data));
  g_assert_cmpstr (data, ==, serialize_data);

  if (g_test_verbose ())
    g_print ("TestObject:\n%s\n", data);

  g_free (data);
  g_object_unref (obj);
}
