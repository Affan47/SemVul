close_moved_tempfile (GVfsBackendSftp *backend,
                      int reply_type,
                      GDataInputStream *reply,
                      guint32 len,
                      GVfsJob *job,
                      gpointer user_data)
{
  SftpHandle *handle;

  handle = user_data;

  if (reply_type == SSH_FXP_STATUS)
    result_from_status (job, reply, -1, -1);
  else
    g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_FAILED,
                      _("Invalid reply received"));


  sftp_handle_free (handle);
}
