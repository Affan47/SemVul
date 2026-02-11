query_info_fstat_reply (GVfsBackendSftp *backend,
                        int reply_type,
                        GDataInputStream *reply,
                        guint32 len,
                        GVfsJob *job,
                        gpointer user_data)
{
  QueryInfoFStatData *data = user_data;
  GFileInfo *file_info;
  GFileAttributeMatcher *attribute_matcher;

  file_info = data->info;
  attribute_matcher = data->attribute_matcher;
  g_slice_free (QueryInfoFStatData, data);

  if (reply_type == SSH_FXP_STATUS)
    {
      result_from_status (job, reply, -1, -1);
      return;
    }

  if (reply_type != SSH_FXP_ATTRS)
    {
      g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_FAILED,
                        _("Invalid reply received"));
      return;
    }

  parse_attributes (backend,
                    file_info,
                    NULL,
                    reply,
                    attribute_matcher);

  g_vfs_job_succeeded (G_VFS_JOB (job));
}
