unmount_cb (GObject       *source_object,
            GAsyncResult  *res,
            gpointer       user_data)
{
  UDisksFilesystem *filesystem = UDISKS_FILESYSTEM (source_object);
  UnmountData *data = user_data;
  GError *error;

  error = NULL;
  if (!udisks_filesystem_call_unmount_finish (filesystem,
                                              res,
                                              &error))
    {
      gvfs_udisks2_utils_udisks_error_to_gio_error (error);


      if (error->code == G_IO_ERROR_BUSY && data->mount_operation != NULL)
        {
          unmount_show_busy (data, udisks_filesystem_get_mount_points (filesystem)[0]);
          goto out;
        }
      g_simple_async_result_take_error (data->simple, error);
    }
  else
    {
      gvfs_udisks2_volume_monitor_update (data->mount->monitor);
      if (data->encrypted != NULL)
        {
          udisks_encrypted_call_lock (data->encrypted,
                                      g_variant_new ("a{sv}", NULL),
                                      data->cancellable,
                                      lock_cb,
                                      data);
          goto out;
        }
    }

  unmount_data_complete (data, FALSE);
 out:
  ;
}
