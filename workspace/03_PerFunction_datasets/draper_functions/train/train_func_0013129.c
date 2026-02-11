do_start_write (GVfsFtpTask *task,
                GFileCreateFlags flags,
                const char *format,
                ...)
{
  va_list varargs;


  g_vfs_ftp_task_setup_data_connection (task);

  va_start (varargs, format);
  g_vfs_ftp_task_sendv (task,
                        G_VFS_FTP_PASS_100 | G_VFS_FTP_FAIL_200,
                        NULL,
                        format,
                        varargs);
  va_end (varargs);

  g_vfs_ftp_task_open_data_connection (task);

  if (!g_vfs_ftp_task_is_in_error (task))
    {

      GVfsFtpConnection *conn = g_vfs_ftp_task_take_connection (task);
      g_vfs_job_open_for_write_set_handle (G_VFS_JOB_OPEN_FOR_WRITE (task->job), conn);
      g_vfs_job_open_for_write_set_can_seek (G_VFS_JOB_OPEN_FOR_WRITE (task->job), FALSE);
    }
}
