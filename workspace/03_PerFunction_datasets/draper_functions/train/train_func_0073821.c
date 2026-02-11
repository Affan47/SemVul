try_mount (GVfsBackend *backend,
           GVfsJobMount *job,
           GMountSpec *mount_spec,
           GMountSource *mount_source,
           gboolean is_automount)
{
  GVfsBackendAfp *afp_backend = G_VFS_BACKEND_AFP (backend);

  const char *host, *volume, *portstr, *user;
  guint16 port = 548;

  host = g_mount_spec_get (mount_spec, "host");
  if (host == NULL)
  {
    g_vfs_job_failed (G_VFS_JOB (job),
                      G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                      _("No hostname specified"));
    return TRUE;
  }

  volume = g_mount_spec_get (mount_spec, "volume");
  if (volume == NULL)
  {
    g_vfs_job_failed (G_VFS_JOB (job),
                      G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                      _("No volume specified"));
    return TRUE;
  }
  afp_backend->volume_name = g_strdup (volume);

  portstr = g_mount_spec_get (mount_spec, "port");
  if (portstr != NULL)
  {
    port = atoi (portstr);
  }

  afp_backend->addr = G_NETWORK_ADDRESS (g_network_address_new (host, port));

  user = g_mount_spec_get (mount_spec, "user");
  afp_backend->user = g_strdup (user);

  return FALSE;
}
