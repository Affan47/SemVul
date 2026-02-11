filterout_libdir_path (void)
{
  char *path;
  char *libdir;


  path = getenv ("PATH");
  if (path)
  {
    libdir = strstr (path, LIBDIR);
    if (libdir)
      setenv ("PATH", libdir + strlen (LIBDIR) + 1, 1);
  }
}
