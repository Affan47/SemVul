guestfs_session_equal(GuestfsSession *session, const gchar *file1, const gchar *file2, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "equal");
    return -1;
  }

  int ret = guestfs_equal (g, file1, file2);
  if (ret == -1) {
    g_set_error_literal(err, GUESTFS_ERROR, 0, guestfs_last_error(g));
    return -1;
  }

  return ret;
}
