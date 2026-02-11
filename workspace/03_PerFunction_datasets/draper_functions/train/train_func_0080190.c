guestfs_session_internal_test_rconstoptstring(GuestfsSession *session, const gchar *val, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "internal_test_rconstoptstring");
    return NULL;
  }

  const char *ret = guestfs_internal_test_rconstoptstring (g, val);

  return ret;
}
