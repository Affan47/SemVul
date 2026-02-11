gxine_lirc_tryload (const char *file)
{
  struct stat st;
  char *fname = g_build_filename (g_get_home_dir(), file, NULL);

  if (stat (fname, &st))
  {
    if (errno == ENOENT)
    {
      free (fname);
      return 1;
    }
    g_printerr (_("lirc: problem with ~/%s: %s\n"), file, strerror (errno));
    free (fname);
    return 1;
  }

  if (lirc_readconfig (fname, &lircconfig, NULL) != 0)
  {
    g_printerr(_("lirc: lirc_readconfig of %s failed\n"), fname);
    free (fname);
    return 1;
  }

  free (fname);
  return 0;
}
