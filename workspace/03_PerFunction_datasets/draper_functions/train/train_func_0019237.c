guestfs_session_mke2journal_U(GuestfsSession *session, gint32 blocksize, const gchar *uuid, const gchar *device, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "mke2journal_U");
    return FALSE;
  }

  int ret = guestfs_mke2journal_U (g, blocksize, uuid, device);
  if (ret == -1) {
    g_set_error_literal(err, GUESTFS_ERROR, 0, guestfs_last_error(g));
    return FALSE;
  }

  return TRUE;
}
