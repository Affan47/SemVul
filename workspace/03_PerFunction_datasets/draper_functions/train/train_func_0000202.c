recent_backend_open_for_read (GVfsBackend        *vfs_backend,
                              GVfsJobOpenForRead *job,
                              const char         *filename)
{
  GVfsBackendRecent *backend = G_VFS_BACKEND_RECENT (vfs_backend);
  GError *error = NULL;

  if (filename[1] == '\0')
    g_set_error_literal (&error, G_IO_ERROR, G_IO_ERROR_IS_DIRECTORY,
                         _("Can't open directory"));

  else
    {
      GFile *real;

      real = recent_backend_get_file (backend, filename, NULL, &error);

      if (real)
        {
          GFileInputStream *stream;

          stream = g_file_read (real, G_VFS_JOB (job)->cancellable, &error);
          g_object_unref (real);

          if (stream)
            {
              g_vfs_job_open_for_read_set_handle (job, stream);
              g_vfs_job_open_for_read_set_can_seek (job, TRUE);
              g_vfs_job_succeeded (G_VFS_JOB (job));

              return TRUE;
            }
        }
    }

  g_vfs_job_failed_from_error (G_VFS_JOB (job), error);
  g_error_free (error);

  return TRUE;
}
