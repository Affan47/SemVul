digest_options_callback (GOptionContext *context,
                         GOptionGroup *group,
                         gpointer      data,
                         GError      **error)
{
  TerminalOptions *options = data;
  InitialTab    *it;

  if (options->execute)
    {
      if (options->exec_argv == NULL)
        {
          g_set_error (error,
                       G_OPTION_ERROR,
                       G_OPTION_ERROR_BAD_VALUE,
                       _("Option \"%s\" requires specifying the command to run"
                         " on the rest of the command line"),
                       "--execute/-x");
          return FALSE;
        }


      it = ensure_top_tab (options);
      it->exec_argv = options->exec_argv;
      options->exec_argv = NULL;
    }

  return TRUE;
}
