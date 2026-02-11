read_sockets (const char    *dir,
              SocketEntry ***entries_p,
              int           *n_entries_p)
{
  DIR   *dirh;
  struct dirent *dent;
  SocketEntry **entries;
  int n_entries;
  int allocated;

  n_entries = 0;
  allocated = 2;
  entries = xmalloc (sizeof (SocketEntry*) * allocated);

  dirh = opendir (dir);
  if (dirh == NULL)
    {
      fprintf (stderr, "Failed to open directory %s: %s\n",
               dir, strerror (errno));
      exit (1);
    }

  while ((dent = readdir (dirh)))
    {
      SocketEntry *se;

      if (strncmp (dent->d_name, "dbus-", 5) != 0)
        continue;

      se = socket_entry_new (dir, dent->d_name);

      if (n_entries == allocated)
        {
          allocated *= 2;
          entries = xrealloc (entries, sizeof (SocketEntry*) * allocated);
        }

      entries[n_entries] = se;
      n_entries += 1;
    }

  closedir (dirh);

  *entries_p = entries;
  *n_entries_p = n_entries;
}
