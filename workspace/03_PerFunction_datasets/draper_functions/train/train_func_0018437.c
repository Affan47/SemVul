main (int argc, char *argv[])
{
  GError *error;
  GOptionContext *context;
  GFile *file;
  gchar *param;
  gchar *summary;
  gboolean res;

  setlocale (LC_ALL, "");

  bindtextdomain (GETTEXT_PACKAGE, GVFS_LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);

  error = NULL;
  param = g_strdup_printf ("[%s...]", _("LOCATION"));
  summary = _("Show information about locations.");

  context = g_option_context_new (param);
  g_option_context_set_summary (context, summary);
  g_option_context_add_main_entries (context, entries, GETTEXT_PACKAGE);
  g_option_context_parse (context, &argc, &argv, &error);
  g_option_context_free (context);
  g_free (param);

  if (error != NULL)
    {
      g_printerr (_("Error parsing commandline options: %s\n"), error->message);
      g_printerr ("\n");
      g_printerr (_("Try \"%s --help\" for more information."), g_get_prgname ());
      g_printerr ("\n");
      g_error_free (error);
      return 1;
    }

  res = TRUE;
  if (argc > 1)
    {
      int i;

      for (i = 1; i < argc; i++) {
	file = g_file_new_for_commandline_arg (argv[i]);
	if (writable)
	  res = get_writable_info (file) && res;
	else
	  res = query_info (file) && res;
	g_object_unref (file);
      }
    }

  return res ? 0 : 2;
}
