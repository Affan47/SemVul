netsnmp_dispatch_external_events2(int *count,
                                       netsnmp_large_fd_set *readfds,
                                       netsnmp_large_fd_set *writefds,
                                       netsnmp_large_fd_set *exceptfds)
{
  int i;
  for (i = 0;
       *count && (i < external_readfdlen) && !external_fd_unregistered; i++) {
      if (NETSNMP_LARGE_FD_ISSET(external_readfd[i], readfds)) {
          DEBUGMSGTL(("fd_event_manager:netsnmp_dispatch_external_events",
                     "readfd[%d] = %d\n", i, external_readfd[i]));
          external_readfdfunc[i] (external_readfd[i],
                                  external_readfd_data[i]);
          NETSNMP_LARGE_FD_CLR(external_readfd[i], readfds);
          (*count)--;
      }
  }
  for (i = 0;
       *count && (i < external_writefdlen) && !external_fd_unregistered; i++) {
      if (NETSNMP_LARGE_FD_ISSET(external_writefd[i], writefds)) {
          DEBUGMSGTL(("fd_event_manager:netsnmp_dispatch_external_events",
                     "writefd[%d] = %d\n", i, external_writefd[i]));
          external_writefdfunc[i] (external_writefd[i],
                                   external_writefd_data[i]);
          NETSNMP_LARGE_FD_CLR(external_writefd[i], writefds);
          (*count)--;
      }
  }
  for (i = 0;
       *count && (i < external_exceptfdlen) && !external_fd_unregistered; i++) {
      if (NETSNMP_LARGE_FD_ISSET(external_exceptfd[i], exceptfds)) {
          DEBUGMSGTL(("fd_event_manager:netsnmp_dispatch_external_events",
                     "exceptfd[%d] = %d\n", i, external_exceptfd[i]));
          external_exceptfdfunc[i] (external_exceptfd[i],
                                    external_exceptfd_data[i]);
          NETSNMP_LARGE_FD_CLR(external_exceptfd[i], exceptfds);
          (*count)--;
      }
  }
}
