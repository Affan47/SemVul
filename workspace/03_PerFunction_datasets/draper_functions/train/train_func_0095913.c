g_vfs_afp_server_mount_volume_sync (GVfsAfpServer *server,
                                    const char    *volume_name,
                                    GCancellable  *cancellable,
                                    GError **error)
{
  GVfsAfpVolume *volume;

  volume = g_vfs_afp_volume_new (server, server->priv->conn);
  if (!g_vfs_afp_volume_mount_sync (volume, volume_name, cancellable, error))
  {
    g_object_unref (volume);
    return NULL;
  }

  return volume;
}
