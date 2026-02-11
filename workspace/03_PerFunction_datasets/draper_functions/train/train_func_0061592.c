read_data_cb (GObject *object, GAsyncResult *res, gpointer user_data)
{
  GInputStream *input = G_INPUT_STREAM (object);
  GVfsAfpConnection *afp_connection = G_VFS_AFP_CONNECTION (user_data);
  GVfsAfpConnectionPrivate *priv = afp_connection->priv;

  gboolean result;
  GError *err = NULL;

  if (g_atomic_int_get (&priv->atomic_state) == STATE_PENDING_CLOSE)
  {
    if (!priv->send_loop_running)
      close_connection (afp_connection);
    return;
  }

  result = read_all_finish (input, res, NULL, &err);
  if (!result)
  {
    if (g_error_matches (err, G_IO_ERROR, G_IO_ERROR_CLOSED))
    {
      g_message (_("Host closed connection"));
      exit(0);
    }
    else
    {
      g_error ("FAIL!!! \"%s\"\n", err->message);
    }
  }

  dispatch_reply (afp_connection);

  if (priv->free_reply_buf)
    g_free (priv->reply_buf);
  priv->reply_buf = NULL;

  read_reply (afp_connection);
}
