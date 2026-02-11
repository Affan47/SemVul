push_create_temp (SftpPushHandle *handle)
{
  GDataOutputStream *command;
  char *dirname;
  char basename[] = ".giosaveXXXXXX";


  handle->temp_count++;

  if (handle->temp_count == 100)
    {
      g_vfs_job_failed (handle->job, G_IO_ERROR, G_IO_ERROR_FAILED,
                        _("Unable to create temporary file"));
      sftp_push_handle_free (handle);
      return;
    }

  g_free (handle->tempname);
  dirname = g_path_get_dirname (handle->op_job->destination);
  random_text (basename + 8);
  handle->tempname = g_build_filename (dirname, basename, NULL);
  g_free (dirname);

  command = new_command_stream (handle->backend, SSH_FXP_OPEN);
  put_string (command, handle->tempname);
  g_data_output_stream_put_uint32 (command, SSH_FXF_WRITE|SSH_FXF_CREAT|SSH_FXF_EXCL,  NULL, NULL);
  g_data_output_stream_put_uint32 (command, 0, NULL, NULL);
  queue_command_stream_and_free (handle->backend, command, push_create_temp_reply, handle->job, handle);
}
