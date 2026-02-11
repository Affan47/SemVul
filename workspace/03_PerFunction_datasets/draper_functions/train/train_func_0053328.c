do_query_info_on_write (GVfsBackend *backend,
			GVfsJobQueryInfoWrite *job,
			GVfsBackendHandle handle,
			GFileInfo *info,
			GFileAttributeMatcher *attribute_matcher)
{
  GFileOutputStream *out;
  GError *error;
  GFileInfo *info2;

  g_print ("do_query_info_on_write\n");

  out = (GFileOutputStream *)handle;

  error = NULL;
  info2 = g_file_output_stream_query_info (out, job->attributes,
					  G_VFS_JOB (job)->cancellable,
					  &error);
  if (info2 == NULL)
    {
      g_vfs_job_failed_from_error (G_VFS_JOB (job), error);
      g_error_free (error);
    }
  else
    {
      g_file_info_copy_into (info2, info);
      g_object_unref (info2);
      g_vfs_job_succeeded (G_VFS_JOB (job));
    }
}
