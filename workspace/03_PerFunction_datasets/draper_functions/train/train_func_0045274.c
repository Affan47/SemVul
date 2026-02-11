power_off_cb (GObject      *source_object,
              GAsyncResult *res,
              gpointer      user_data)
{
  StopData *data = user_data;
  GError *error;

  error = NULL;
  if (!udisks_drive_call_power_off_finish (UDISKS_DRIVE (source_object), res, &error))
    {
      gvfs_udisks2_utils_udisks_error_to_gio_error (error);
      g_simple_async_result_take_error (data->simple, error);
    }

  if (data->mount_operation != NULL)
    {

      if (error != NULL)
        g_signal_emit_by_name (data->mount_operation, "aborted");

      gvfs_udisks2_unmount_notify_stop (data->mount_operation);
    }

  g_simple_async_result_complete (data->simple);
  stop_data_free (data);
}
