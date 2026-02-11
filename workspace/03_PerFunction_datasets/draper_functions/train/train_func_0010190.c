cancel_operation_reply_cb (GVfsRemoteVolumeMonitor *proxy,
                           GAsyncResult *res,
                           gpointer user_data)
{
  gboolean out_WasCancelled;
  GError *error = NULL;

  if (!gvfs_remote_volume_monitor_call_cancel_operation_finish (proxy,
                                                                &out_WasCancelled,
                                                                res,
                                                                &error))
    {
      g_warning ("Error from CancelOperation(): %s", error->message);
      g_error_free (error);
    }
}
