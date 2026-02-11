recent_backend_create_file_monitor (GVfsBackend          *vfs_backend,
                                    GVfsJobCreateMonitor *job,
                                    const char           *filename,
                                    GFileMonitorFlags     flags)
{
  GVfsBackendRecent *backend = G_VFS_BACKEND_RECENT (vfs_backend);
  GVfsMonitor *monitor;

  if (filename[1])
    monitor = g_vfs_monitor_new (vfs_backend);
  else
    monitor = recent_backend_get_file_monitor (backend, TRUE);

  g_vfs_job_create_monitor_set_monitor (job, monitor);
  g_vfs_job_succeeded (G_VFS_JOB (job));
  g_object_unref (monitor);

  return TRUE;
}
