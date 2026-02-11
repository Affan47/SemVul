do_query_info_on_read (GVfsBackend *backend,
		       GVfsJobQueryInfoRead *job,
		       GVfsBackendHandle handle,
		       GFileInfo *info,
		       GFileAttributeMatcher *attribute_matcher)
{
  int fd, res;
  struct stat statbuf;

  fd = GPOINTER_TO_INT (handle);

  res = fstat (fd, &statbuf);

  if (res == -1)
    {
      int errsv = errno;

      g_vfs_job_failed (G_VFS_JOB (job), G_IO_ERROR,
			g_io_error_from_errno (errsv),
			"Error querying info in file: %s",
			g_strerror (errsv));
    }
  else
    {
      g_file_info_set_size (info, statbuf.st_size);
      g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_DEVICE,
					statbuf.st_dev);
      g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_MODIFIED, statbuf.st_mtime);
      g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_ACCESS, statbuf.st_atime);
      g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_CHANGED, statbuf.st_ctime);

      g_vfs_job_succeeded (G_VFS_JOB (job));
    }
}
