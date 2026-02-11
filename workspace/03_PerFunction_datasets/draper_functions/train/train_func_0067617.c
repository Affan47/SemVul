check_open (GVfsAfpConnection *conn, GError **error)
{
  GVfsAfpConnectionPrivate *priv = conn->priv;


  gint state = g_atomic_int_get (&priv->atomic_state);

  if (state == STATE_INITIAL)
  {
    g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_NOT_INITIALIZED,
                         _("The connection is not opened"));
    return FALSE;
  }

  else if (state == STATE_CLOSED)
  {
    g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_CLOSED,
                         _("The connection is closed"));
    return FALSE;
  }

  return TRUE;
}
