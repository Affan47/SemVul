do_create (GVfsBackend *backend,
	   GVfsJobOpenForWrite *job,
	   const char *filename,
	   GFileCreateFlags flags)
{
  GFile *file;
  GFileOutputStream *out;
  GError *error;

  file = g_vfs_get_file_for_path (g_vfs_get_local (),
				  filename);

  error = NULL;
  out = g_file_create (file, flags, G_VFS_JOB (job)->cancellable, &error);
  g_object_unref (file);
  if (out)
    {
      g_vfs_job_open_for_write_set_can_seek (job, FALSE);
      g_vfs_job_open_for_write_set_handle (job, out);
      g_vfs_job_succeeded (G_VFS_JOB (job));
    }
  else
    {
      g_vfs_job_failed_from_error (G_VFS_JOB (job), error);
      g_error_free (error);
    }
}
