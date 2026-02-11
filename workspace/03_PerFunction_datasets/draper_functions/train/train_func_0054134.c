do_seek_on_read (GVfsBackend *backend,
                  GVfsJobSeekRead *job,
                  GVfsBackendHandle _handle,
                  goffset    offset,
                  GSeekType  type)
{
  GError *error;
  GFileInputStream *stream = _handle;

  error = NULL;
  if (g_seekable_seek (G_SEEKABLE (stream), offset, type,
                       G_VFS_JOB (job)->cancellable, &error))
    {
      g_vfs_job_seek_read_set_offset (job, g_seekable_tell (G_SEEKABLE (stream)));
      g_vfs_job_succeeded (G_VFS_JOB (job));
    }
  else
    {
      g_vfs_job_failed_from_error (G_VFS_JOB (job), error);
      g_error_free (error);
    }
}
