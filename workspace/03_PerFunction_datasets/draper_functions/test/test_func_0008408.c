g_vfs_afp_volume_set_fork_size (GVfsAfpVolume       *volume,
                                gint16               fork_refnum,
                                gint64               size,
                                GCancellable        *cancellable,
                                GAsyncReadyCallback  callback,
                                gpointer             user_data)
{
  GVfsAfpVolumePrivate *priv;
  GVfsAfpCommand *comm;
  GSimpleAsyncResult *simple;

  g_return_if_fail (G_VFS_IS_AFP_VOLUME (volume));

  priv = volume->priv;

  comm = g_vfs_afp_command_new (AFP_COMMAND_SET_FORK_PARMS);

  g_vfs_afp_command_put_byte (comm, 0);


  g_vfs_afp_command_put_int16 (comm, fork_refnum);

  g_vfs_afp_command_put_uint16 (comm, AFP_FILE_BITMAP_EXT_DATA_FORK_LEN_BIT);

  g_vfs_afp_command_put_int64 (comm, size);

  simple = g_simple_async_result_new (G_OBJECT (volume), callback, user_data,
                                      g_vfs_afp_volume_set_fork_size);

  g_vfs_afp_connection_send_command (priv->conn, comm, NULL,
                                     set_fork_parms_cb, cancellable, simple);
  g_object_unref (comm);
}
