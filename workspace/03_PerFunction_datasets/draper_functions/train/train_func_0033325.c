run_query_info (GVfsBackendSmbBrowse *backend,
		GVfsJobQueryInfo *job,
		const char *filename,
		GFileInfo *info,
		GFileAttributeMatcher *matcher)
{
  BrowseEntry *entry;

  g_mutex_lock (&backend->entries_lock);

  entry = find_entry_unlocked (backend, filename);

  if (entry)
    get_file_info_from_entry (backend, entry, info);

  g_mutex_unlock (&backend->entries_lock);

  if (entry)
    g_vfs_job_succeeded (G_VFS_JOB (job));
  else
    g_vfs_job_failed (G_VFS_JOB (job),
		      G_IO_ERROR, G_IO_ERROR_NOT_FOUND,
		      _("File doesn't exist"));
}
