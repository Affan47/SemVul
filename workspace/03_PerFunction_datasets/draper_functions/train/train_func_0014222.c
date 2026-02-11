read_dsi_header_cb (GObject *object, GAsyncResult *res, gpointer user_data)
{
  GInputStream *input = G_INPUT_STREAM (object);
  GVfsAfpConnection *afp_conn = G_VFS_AFP_CONNECTION (user_data);
  GVfsAfpConnectionPrivate *priv = afp_conn->priv;

  gboolean result;
  GError *err = NULL;
  DSIHeader *dsi_header;

  if (g_atomic_int_get (&priv->atomic_state) == STATE_PENDING_CLOSE)
  {
    if (!priv->send_loop_running)
      close_connection (afp_conn);
    return;
  }

  result = read_all_finish (input, res, NULL, &err);
  if (!result)
  {
    g_warning ("FAIL!!! \"%s\"\n", err->message);
    g_error_free (err);
  }

  dsi_header = &priv->read_dsi_header;

  dsi_header->requestID = GUINT16_FROM_BE (dsi_header->requestID);
  dsi_header->errorCode = GUINT32_FROM_BE (dsi_header->errorCode);
  dsi_header->totalDataLength = GUINT32_FROM_BE (dsi_header->totalDataLength);

  if (dsi_header->totalDataLength > 0)
  {
    RequestData *req_data;

    req_data = g_hash_table_lookup (priv->request_hash,
                                    GUINT_TO_POINTER ((guint)dsi_header->requestID));
    if (req_data && req_data->reply_buf)
    {
        priv->reply_buf = req_data->reply_buf;
        priv->free_reply_buf = FALSE;
    }
    else
    {
      priv->reply_buf = g_malloc (dsi_header->totalDataLength);
      priv->free_reply_buf = TRUE;
    }

    read_all_async (input, priv->reply_buf, dsi_header->totalDataLength,
                    0, priv->read_cancellable, read_data_cb, afp_conn);

    return;
  }

  dispatch_reply (afp_conn);
  read_reply (afp_conn);
}
