test_builder_empty (void)
{
  JsonBuilder *builder = json_builder_new ();
  JsonNode *node;
  JsonGenerator *generator;
  gsize length;
  gchar *data;

  json_builder_begin_object (builder);

  json_builder_set_member_name (builder, "a");

  json_builder_begin_object (builder);
  json_builder_end_object (builder);

  json_builder_end_object (builder);

  node = json_builder_get_root (builder);
  g_object_unref (builder);

  generator = json_generator_new ();
  json_generator_set_root (generator, node);
  data = json_generator_to_data (generator, &length);

  if (g_test_verbose ())
    g_print ("Builder empty: '%*s'\n", (int)length, data);

  g_assert_cmpint (length, ==, strlen (empty_object));
  g_assert_cmpstr (data, ==, empty_object);

  g_free (data);
  json_node_free (node);
  g_object_unref (generator);
}
