do_break_directory(GConfEngine* conf, const gchar** args)
{
  if (args == NULL)
    {
      g_printerr (_("Must specify some directories to break\n"));
      return 1;
    }

  while (*args)
    {
      gchar* keys[10] = { NULL };
      gchar* full_keys[10] = { NULL };
      int i;

      i = 0;
      while (i < 10)
        {
          keys[i] = gconf_unique_key();
          full_keys[i] = gconf_concat_dir_and_key(*args, keys[i]);

          ++i;
        }

      g_print (_("Trying to break your application by setting bad values for keys in directory:\n  %s\n"), *args);

      i = 0;
      while (i < 10)
        {
          if (!key_breakage(conf, full_keys[i], BreakageSetBadValues))
            return 1;

          ++i;
        }

      i = 0;
      while (i < 10)
        {
          if (!key_breakage(conf, full_keys[i], BreakageCleanup))
            return 1;

          ++i;
        }

      i = 0;
      while (i < 10)
        {
          g_free(keys[i]);
          g_free(full_keys[i]);

          ++i;
        }

      ++args;
    }

  return 0;
}
