guestfs_session_pwrite_device(GuestfsSession *session, const gchar *device, const guint8 *content, gsize content_size, gint64 offset, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "pwrite_device");
    return -1;
  }

  int ret = guestfs_pwrite_device (g, device, content, content_size, offset);
  if (ret == -1) {
    g_set_error_literal(err, GUESTFS_ERROR, 0, guestfs_last_error(g));
    return -1;
  }

  return ret;
}
