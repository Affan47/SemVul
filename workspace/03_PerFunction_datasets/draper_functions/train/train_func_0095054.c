do_dissociate_schema (GConfEngine *conf, const gchar **args)
{
  GError *err;
  gboolean failed;

  if (!args || args[0] == NULL)
    {
      g_printerr (_("Must specify keys to unapply schema from\n"));
      return 1;
    }

  failed = FALSE;
  while (*args)
    {
      err = NULL;
      if (!gconf_engine_associate_schema (conf, *args, NULL, &err))
        {
          g_printerr (_("Error removing schema name from '%s': %s\n"),
		      *args, err->message);
          g_error_free (err);
          failed = TRUE;
        }

      ++args;
    }

  if (failed)
    return 1;
  else
    return 0;
}
