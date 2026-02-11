_gst_plugin_loader_client_run (void)
{
  GstPluginLoader *l;

  l = plugin_loader_new (NULL);
  if (l == NULL)
    return FALSE;


#ifndef G_OS_WIN32
  {
    int dup_fd;

    dup_fd = dup (0);
    if (dup_fd == -1) {
      GST_ERROR ("Failed to start. Could no dup STDIN, errno %d", errno);
      return FALSE;
    }
    l->fd_r.fd = dup_fd;
    close (0);

    dup_fd = dup (1);
    if (dup_fd == -1) {
      GST_ERROR ("Failed to start. Could no dup STDOUT, errno %d", errno);
      return FALSE;
    }
    l->fd_w.fd = dup_fd;
    close (1);


    dup2 (2, 1);
  }
#else

  l->fd_w.fd = 1;
  l->fd_r.fd = 0;
#endif

  gst_poll_add_fd (l->fdset, &l->fd_w);
  gst_poll_add_fd (l->fdset, &l->fd_r);
  gst_poll_fd_ctl_read (l->fdset, &l->fd_r, TRUE);

  l->is_child = TRUE;

  GST_DEBUG ("Plugin scanner child running. Waiting for instructions");


  while (!l->rx_done && exchange_packets (l));

  plugin_loader_free (l);

  return TRUE;
}
