forced_unregister_mount_callback (GVfsDBusMountTracker *proxy,
                                 GAsyncResult *res,
                                 gpointer user_data)
{
  GVfsDaemon *daemon;
  GVfsBackend *backend;
  GError *error = NULL;

  g_return_if_fail (G_VFS_IS_BACKEND (user_data));

  g_debug ("forced_unregister_mount_callback\n");
  if (! gvfs_dbus_mount_tracker_call_unregister_mount_finish (proxy,
                                                              res,
                                                              &error))
    {
      g_dbus_error_strip_remote_error (error);
      g_warning ("Error unregistering mount: %s (%s, %d)\n",
                  error->message, g_quark_to_string (error->domain), error->code);
      g_error_free (error);
    }


  backend = G_VFS_BACKEND (user_data);
  daemon = g_vfs_backend_get_daemon (backend);
  g_vfs_daemon_close_active_channels (daemon, backend);
  g_vfs_job_source_closed (G_VFS_JOB_SOURCE (backend));

}
