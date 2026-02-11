on_mount_operation_reply (GMountOperation       *mount_operation,
                          GMountOperationResult result,
                          gpointer              user_data)
{
  MountData *data = user_data;


  if (data->mount_operation_reply_handler_id != 0)
    {
      g_signal_handler_disconnect (data->mount_operation, data->mount_operation_reply_handler_id);
      data->mount_operation_reply_handler_id = 0;
    }
  if (data->mount_operation_aborted_handler_id != 0)
    {
      g_signal_handler_disconnect (data->mount_operation, data->mount_operation_aborted_handler_id);
      data->mount_operation_aborted_handler_id = 0;
    }

  if (result != G_MOUNT_OPERATION_HANDLED)
    {
      if (result == G_MOUNT_OPERATION_ABORTED)
        {

          g_simple_async_result_set_error (data->simple,
                                           G_IO_ERROR,
                                           G_IO_ERROR_FAILED_HANDLED,
                                           "Password dialog aborted (user should never see this error since it is G_IO_ERROR_FAILED_HANDLED)");
        }
      else
        {
          g_simple_async_result_set_error (data->simple,
                                           G_IO_ERROR,
                                           G_IO_ERROR_PERMISSION_DENIED,
                                           "Expected G_MOUNT_OPERATION_HANDLED but got %d", result);
        }
      g_simple_async_result_complete (data->simple);
      mount_data_free (data);
      goto out;
    }

  data->passphrase = g_strdup (g_mount_operation_get_password (mount_operation));
  data->password_save = g_mount_operation_get_password_save (mount_operation);


  do_unlock (data);

 out:
  ;
}
