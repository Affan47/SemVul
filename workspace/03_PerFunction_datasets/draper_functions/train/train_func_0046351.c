try_query_info (GVfsBackend           *backend,
                GVfsJobQueryInfo      *job,
                const char            *filename,
                GFileQueryInfoFlags    flags,
                GFileInfo             *info,
                GFileAttributeMatcher *attribute_matcher)
{
  SoupMessage *msg;
  SoupURI     *uri;

  if (g_file_attribute_matcher_matches_only (attribute_matcher,
                                             G_FILE_ATTRIBUTE_THUMBNAIL_PATH))
    {
      g_vfs_job_succeeded (G_VFS_JOB (job));
      return TRUE;
    }

  uri = http_backend_get_mount_base (backend);
  msg = soup_message_new_from_uri (SOUP_METHOD_HEAD, uri);

  http_backend_queue_message (backend, msg, query_info_ready, job);

  return TRUE;
}
