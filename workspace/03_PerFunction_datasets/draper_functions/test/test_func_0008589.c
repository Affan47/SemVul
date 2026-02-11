find_mount_entry_for_file (GFile *file)
{
  GUnixMountEntry *entry;
  char *pathname;

  pathname = g_file_get_path (file);
  do
    {
      char *slash;

      slash = strrchr (pathname, '/');


      if (slash == pathname)
        slash++;

      *slash = '\0';

      entry = g_unix_mount_at (pathname, NULL);
    }
  while (entry == NULL && pathname[1]);

  g_free (pathname);


  g_assert (entry != NULL);

  return entry;
}
