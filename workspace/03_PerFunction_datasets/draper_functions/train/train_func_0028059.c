evd_dbus_daemon_initable_init (GInitable     *initable,
                               GCancellable  *cancellable,
                               GError       **error)
{
  EvdDBusDaemon *self = EVD_DBUS_DAEMON (initable);
  gint stdout_fd;

  self->priv->pid = spawn_dbus_daemon (self->priv->config_file,
                                       &stdout_fd,
                                       error);

  if (self->priv->pid <= 0)
    {
      return FALSE;
    }
  else
    {
      gchar buf[256] = { 0, };
      gchar **lines;
      gssize size;

      errno = 0;
      size = read (stdout_fd, buf, 256);
      if (size >= 0)
        {
          lines = g_strsplit (buf, "\n", 0);
          self->priv->addr = g_strdup (lines[0]);
          g_strfreev (lines);

          return TRUE;
        }
      else
        {
          g_set_error (error,
                       EVD_ERRNO_ERROR,
                       errno,
                       "Failed to D-Bus daemon address from stdout: %s",
                       strerror (errno));

          return FALSE;
        }
    }
}
