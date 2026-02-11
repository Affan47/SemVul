test_rest3 (void)
{
  GOptionEntry entries [] = {
      { "test", 0, 0, G_OPTION_ARG_NONE, &test_boolean, NULL, NULL },
      { G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_STRING_ARRAY, &test_array, NULL, NULL },
      { NULL }
  };

  context = g_option_context_new (NULL);
  g_option_context_add_main_entries (context, entries, NULL);


  argv = split_string ("program foo --test bar", &argc);

  cut_assert (g_option_context_parse (context, &argc, &argv, &error));


  cut_assert (test_boolean);
  cut_assert_equal_string ("foo", test_array[0]);
  cut_assert_equal_string ("bar", test_array[1]);
  cut_assert_null (argv[2]);

  g_strfreev (test_array);
}
