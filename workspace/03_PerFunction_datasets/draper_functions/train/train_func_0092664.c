handle_sockets (SocketEntry **entries,
                int           n_entries)
{
  int i;
  int n_unknown;

  n_unknown = 0;

  i = 0;
  while (i < n_entries)
    {
      SocketEntry *se;
      SocketStatus status;

      se = entries[i];
      ++i;

      if (se->fd >= 0)
        {
          fprintf (stderr, "Internal error, socket has fd  kept open while status = %d\n",
                   se->status);
          exit (1);
        }

      if (se->status != SOCKET_UNKNOWN)
        continue;

      status = open_socket (se);

      switch (status)
        {
        case SOCKET_DEAD:
          cleaned_count += 1;
          if (unlink (se->name) < 0)
            {
              fprintf (stderr, "Warning: Failed to delete %s: %s\n",
                       se->name, strerror (errno));

              se->status = SOCKET_FAILED_TO_HANDLE;
            }
          else
            se->status = SOCKET_UNLINKED;
          break;

        case SOCKET_ALIVE:
          alive_count += 1;


        case SOCKET_FAILED_TO_HANDLE:
        case SOCKET_UNKNOWN:
          se->status = status;
          break;

        case SOCKET_UNLINKED:
          fprintf (stderr, "Bad status from open_socket(), should not happen\n");
          exit (1);
          break;
        }

      if (se->fd >= 0)
        {
          close (se->fd);
          se->fd = -1;
        }

      if (se->status == SOCKET_UNKNOWN)
        n_unknown += 1;
    }

  return n_unknown == 0;
}
