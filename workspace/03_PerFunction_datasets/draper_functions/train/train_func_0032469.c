push_open_reply (GVfsBackendSftp *backend,
                 int reply_type,
                 GDataInputStream *reply,
                 guint32 len,
                 GVfsJob *job,
                 gpointer user_data)
{
  SftpPushHandle *handle = user_data;

  if (reply_type == SSH_FXP_STATUS)
    {
      guint32 code = read_status_code (reply);
      if (code == SSH_FX_NO_SUCH_FILE)
        not_dir_or_not_exist_error (backend, job, handle->op_job->destination);
      else if (code == SSH_FX_FAILURE)
        {
          if (handle->op_job->flags & G_FILE_COPY_OVERWRITE)
            {


              GDataOutputStream *command = new_command_stream (backend, SSH_FXP_LSTAT);
              put_string (command, handle->op_job->destination);
              queue_command_stream_and_free (backend, command, push_open_stat_reply, job, handle);
              return;
            }
          else
            result_from_status_code (job, code, G_IO_ERROR_EXISTS, -1);
        }
      else
        g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_FAILED,
                          _("Invalid reply received"));
    }
  else if (reply_type != SSH_FXP_HANDLE)
    g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_FAILED,
                      _("Invalid reply received"));
  else
    {
      handle->raw_handle = read_data_buffer (reply);
      push_enqueue_request (handle);
    }

  sftp_push_handle_free (handle);
}
