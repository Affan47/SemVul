test_missing_arg (void)
{
  gchar *arg = NULL;
  GOptionEntry entries [] =
    { { "test", 't', 0, G_OPTION_ARG_STRING, &arg, NULL, NULL },
      { NULL } };

  g_option_context_add_main_entries (context, entries, NULL);


  argv = split_string ("program --test", &argc);

  cut_assert (!g_option_context_parse (context, &argc, &argv, &error));
  g_clear_error (&error);


  argv = split_string ("program --t", &argc);

  cut_assert (!g_option_context_parse (context, &argc, &argv, &error));
}
