gst_plugin_loader_try_helper (GstPluginLoader * loader, gchar * location)
{
  char *argv[5] = { NULL, };
  int c = 0;

#if defined (__APPLE__) && defined (USR_BIN_ARCH_SWITCH)
  if (gst_plugin_loader_use_usr_bin_arch ()) {
    argv[c++] = (char *) "/usr/bin/arch";
    argv[c++] = (char *) USR_BIN_ARCH_SWITCH;
  }
#endif
  argv[c++] = location;
  argv[c++] = (char *) "-l";
  argv[c++] = NULL;

  if (c > 3) {
    GST_LOG ("Trying to spawn gst-plugin-scanner helper at %s with arch %s",
        location, argv[1]);
  } else {
    GST_LOG ("Trying to spawn gst-plugin-scanner helper at %s", location);
  }

  if (!g_spawn_async_with_pipes (NULL, argv, NULL,
          G_SPAWN_DO_NOT_REAP_CHILD  ,
          NULL, NULL, &loader->child_pid, &loader->fd_w.fd, &loader->fd_r.fd,
          NULL, NULL))
    return FALSE;

  gst_poll_add_fd (loader->fdset, &loader->fd_w);
  gst_poll_add_fd (loader->fdset, &loader->fd_r);

  gst_poll_fd_ctl_read (loader->fdset, &loader->fd_r, TRUE);

  loader->tx_buf_write = loader->tx_buf_read = 0;

  put_packet (loader, PACKET_VERSION, 0, NULL, 0);
  if (!plugin_loader_sync_with_child (loader))
    return FALSE;

  loader->child_running = TRUE;

  return TRUE;
}
