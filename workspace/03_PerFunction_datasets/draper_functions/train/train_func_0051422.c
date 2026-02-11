sftp_pull_handle_free (SftpPullHandle *handle)
{
  if (handle->size != PULL_SIZE_INCOMPLETE &&
      (!handle->output || !g_output_stream_has_pending (handle->output)) &&
      handle->num_req == 0)
    {
      if (handle->raw_handle)
        {
          GDataOutputStream *command = new_command_stream (handle->backend, SSH_FXP_CLOSE);
          put_data_buffer (command, handle->raw_handle);
          queue_command_stream_and_free (handle->backend, command, NULL, handle->job, NULL);
          data_buffer_free (handle->raw_handle);
        }
      g_clear_object (&handle->output);
      g_object_unref(handle->backend);
      g_object_unref(handle->op_job);
      g_object_unref(handle->dest);
      g_list_free_full (handle->queued_writes, (GDestroyNotify)pull_request_free);
      g_slice_free (SftpPullHandle, handle);
    }
}
