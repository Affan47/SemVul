g_vfs_afp_server_logout_sync (GVfsAfpServer *server,
                              GCancellable  *cancellable,
                              GError       **error)
{
  GVfsAfpServerPrivate *priv;
  GVfsAfpCommand *comm;
  GVfsAfpReply *reply;
  gint32 res_code;
  gboolean res = FALSE;

  g_return_val_if_fail (G_VFS_IS_AFP_SERVER (server), FALSE);

  priv = server->priv;

  comm = g_vfs_afp_command_new (AFP_COMMAND_LOGOUT);

  g_vfs_afp_command_put_byte (comm, 0);

  reply = g_vfs_afp_connection_send_command_sync (priv->conn, comm, cancellable, error);
  g_object_unref (comm);
  if (!reply) {
    g_vfs_afp_connection_close_sync (priv->conn, cancellable, NULL);
    goto done;
  }

  res_code = g_vfs_afp_reply_get_result_code (reply);
  g_object_unref (reply);
  if (res_code != AFP_RESULT_NO_ERROR) {
    g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_FAILED, _("Unable to disconnect from the server."));
    g_vfs_afp_connection_close_sync (priv->conn, cancellable, NULL);
    goto done;
  }

  res = g_vfs_afp_connection_close_sync (priv->conn, cancellable, error);

done:
  g_clear_object (&priv->conn);
  return res;
}
