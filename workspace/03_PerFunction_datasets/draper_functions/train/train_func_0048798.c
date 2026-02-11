try_seek_on_read (GVfsBackend *backend,
                  GVfsJobSeekRead *job,
                  GVfsBackendHandle _handle,
                  goffset    offset,
                  GSeekType  type)
{
  SftpHandle *handle = _handle;
  GVfsBackendSftp *op_backend = G_VFS_BACKEND_SFTP (backend);
  GDataOutputStream *command;

  switch (job->seek_type)
    {
    case G_SEEK_CUR:
      handle->offset += job->requested_offset;
      break;
    case G_SEEK_SET:
      handle->offset = job->requested_offset;
      break;
    case G_SEEK_END:
      command = new_command_stream (op_backend,
                                    SSH_FXP_FSTAT);
      put_data_buffer (command, handle->raw_handle);
      queue_command_stream_and_free (op_backend, command, seek_read_fstat_reply, G_VFS_JOB (job), handle);
      return TRUE;
    }

  if (handle->offset < 0)
    handle->offset = 0;

  g_vfs_job_seek_read_set_offset (job, handle->offset);
  g_vfs_job_succeeded (G_VFS_JOB (job));

  return TRUE;
}
