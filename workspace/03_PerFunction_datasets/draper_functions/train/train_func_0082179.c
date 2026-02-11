test_empty_object (void)
{
  JsonParser *parser;
  GError *error = NULL;

  parser = json_parser_new ();
  g_assert (JSON_IS_PARSER (parser));

  if (g_test_verbose ())
    g_print ("checking json_parser_load_from_data with empty object...\n");

  if (!json_parser_load_from_data (parser, test_empty_object_string, -1, &error))
    {
      if (g_test_verbose ())
        g_print ("Error: %s\n", error->message);
      g_error_free (error);
      g_object_unref (parser);
      exit (1);
    }
  else
    {
      JsonNode *root;
      JsonObject *object;

      g_assert (NULL != json_parser_get_root (parser));

      if (g_test_verbose ())
        g_print ("checking root node is an object...\n");
      root = json_parser_get_root (parser);
      g_assert (json_node_get_parent (root) == NULL);
      g_assert_cmpint (JSON_NODE_TYPE (root), ==, JSON_NODE_OBJECT);
      g_assert (json_node_get_parent (root) == NULL);

      object = json_node_get_object (root);
      g_assert (object != NULL);

      if (g_test_verbose ())
        g_print ("checking object is empty...\n");
      g_assert_cmpint (json_object_get_size (object), ==, 0);
    }

  g_object_unref (parser);
}
