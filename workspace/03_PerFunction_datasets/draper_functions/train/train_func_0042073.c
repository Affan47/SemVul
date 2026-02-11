g_proxy_volume_eject_with_operation (GVolume             *volume,
                                     GMountUnmountFlags   flags,
                                     GMountOperation     *mount_operation,
                                     GCancellable        *cancellable,
                                     GAsyncReadyCallback  callback,
                                     gpointer             user_data)
{
  GProxyVolume *proxy_volume = G_PROXY_VOLUME (volume);
  GProxyDrive *drive;

  drive = NULL;
  G_LOCK (proxy_volume);
  if (proxy_volume->drive_id != NULL && strlen (proxy_volume->drive_id) > 0)
    {
      drive = g_proxy_volume_monitor_get_drive_for_id (proxy_volume->volume_monitor,
                                                       proxy_volume->drive_id);
    }
  G_UNLOCK (proxy_volume);

  if (drive != NULL)
    {
      EjectWrapperOp *data;
      data = g_new0 (EjectWrapperOp, 1);
      data->object = g_object_ref (volume);
      data->callback = callback;
      data->user_data = user_data;
      g_drive_eject_with_operation (G_DRIVE (drive), flags, mount_operation, cancellable, eject_wrapper_callback, data);
      g_object_unref (drive);
    }
}
