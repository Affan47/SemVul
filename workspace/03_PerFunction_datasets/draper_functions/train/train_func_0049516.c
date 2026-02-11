test_rest2 (void)
{
  gboolean retval;
  int argc;
  GOptionEntry entries [] = {
      { "test", 0, 0, G_OPTION_ARG_NONE, &test_boolean, NULL, NULL },
      { NULL }
  };

  g_option_context_add_main_entries (context, entries, NULL);


  argv = split_string ("program foo --test -- -bar", &argc);

  retval = g_option_context_parse (context, &argc, &argv, &error);
  cut_assert (retval);


  cut_assert (test_boolean);
  cut_assert_equal_string ("program", argv[0]);
  cut_assert_equal_string ("foo", argv[1]);
  cut_assert_equal_string ("--", argv[2]);
  cut_assert_equal_string ("-bar", argv[3]);
  cut_assert_null (argv[4]);
}
