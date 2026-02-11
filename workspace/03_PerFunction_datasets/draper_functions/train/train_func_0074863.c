gvfs_udisks2_volume_eject_with_operation (GVolume              *_volume,
                                          GMountUnmountFlags   flags,
                                          GMountOperation     *mount_operation,
                                          GCancellable        *cancellable,
                                          GAsyncReadyCallback  callback,
                                          gpointer             user_data)
{
  GVfsUDisks2Volume *volume = GVFS_UDISKS2_VOLUME (_volume);
  GVfsUDisks2Drive *drive;

  drive = NULL;
  if (volume->drive != NULL)
    drive = g_object_ref (volume->drive);

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
  else
    {
      GSimpleAsyncResult *simple;
      simple = g_simple_async_result_new_error (G_OBJECT (volume),
                                                callback,
                                                user_data,
                                                G_IO_ERROR,
                                                G_IO_ERROR_FAILED,
                                                _("Operation not supported by backend"));
      g_simple_async_result_complete (simple);
      g_object_unref (simple);
    }
}
