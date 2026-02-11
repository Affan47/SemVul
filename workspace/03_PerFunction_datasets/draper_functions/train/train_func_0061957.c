recent_backend_get_file_monitor (GVfsBackendRecent *backend,
                                 gboolean           create)
{
  if (backend->file_monitor == NULL && create == FALSE)
    return NULL;

  else if (backend->file_monitor == NULL)
    {


      backend->file_monitor = g_vfs_monitor_new (G_VFS_BACKEND (backend));
    }

  return g_object_ref (backend->file_monitor);
}
