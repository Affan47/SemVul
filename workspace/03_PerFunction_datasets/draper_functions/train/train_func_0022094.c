test_ignore1 (void)
{
  gchar **argv_copy;
  gchar *arg;
  GOptionEntry entries [] =
    { { "test", 0, 0, G_OPTION_ARG_NONE, &test_boolean, NULL, NULL },
      { NULL } };

  g_option_context_set_ignore_unknown_options (context, TRUE);
  g_option_context_add_main_entries (context, entries, NULL);


  argv = split_string ("program --test --hello", &argc);
  argv_copy = copy_stringv (argv, argc);

  cut_assert (g_option_context_parse (context, &argc, &argv, &error));


  arg = join_stringv (argc, argv);
  cut_assert_equal_string ("program --hello", arg);

  g_free (arg);
  g_strfreev (argv_copy);
  g_free (argv);
  argv = NULL;
}
