try_set_attribute (GVfsBackend *backend,
                   GVfsJobSetAttribute *job,
                   const char *filename,
                   const char *attribute,
                   GFileAttributeType type,
                   gpointer value_p,
                   GFileQueryInfoFlags flags)
{
  GVfsBackendAfp *afp_backend = G_VFS_BACKEND_AFP (backend);

  if ((strcmp (attribute, G_FILE_ATTRIBUTE_UNIX_MODE) == 0 ||
       strcmp (attribute, G_FILE_ATTRIBUTE_UNIX_UID) == 0 ||
       strcmp (attribute, G_FILE_ATTRIBUTE_UNIX_GID) == 0)
      && g_vfs_afp_volume_get_attributes (afp_backend->volume) & AFP_VOLUME_ATTRIBUTES_BITMAP_SUPPORTS_UNIX_PRIVS)
    {
      if (type != G_FILE_ATTRIBUTE_TYPE_UINT32)
      {
        g_vfs_job_failed (G_VFS_JOB (job),
                          G_IO_ERROR,
                          G_IO_ERROR_INVALID_ARGUMENT,
                          "%s",
                          _("Invalid attribute type (uint32 expected)"));
        return TRUE;
      }

      g_vfs_afp_volume_get_filedir_parms (afp_backend->volume, filename,
                                          AFP_FILEDIR_BITMAP_UNIX_PRIVS_BIT,
                                          AFP_FILEDIR_BITMAP_UNIX_PRIVS_BIT,
                                          G_VFS_JOB (job)->cancellable,
                                          set_attribute_get_filedir_parms_cb,
                                          job);
      return TRUE;
    }

  else {
    g_vfs_job_failed (G_VFS_JOB (job),
                      G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED,
                      _("Operation unsupported"));
    return TRUE;
  }
}
