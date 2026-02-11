pull_write_cb (GObject *source, GAsyncResult *res, gpointer user_data)
{
  PullRequest *request = user_data;
  SftpPullHandle *handle = request->handle;
  GError *error = NULL;
  gssize n_written;

  n_written = g_output_stream_write_finish (handle->output, res, &error);
  if (n_written == -1)
    {
      g_vfs_job_failed_from_error (handle->job, error);
      g_error_free (error);
      pull_request_free (request);
      sftp_pull_handle_free (handle);
      return;
    }

  handle->n_written += n_written;
  request->write_offset += n_written;


  if (request->write_offset < request->response_len)
    {
      g_output_stream_write_async (handle->output,
                                   request->buffer + request->write_offset,
                                   request->response_len - request->write_offset,
                                   G_PRIORITY_DEFAULT,
                                   NULL,
                                   pull_write_cb, request);
      return;
    }

  if (handle->size >= 0)
    g_vfs_job_progress_callback (handle->n_written, handle->size, handle->job);

  pull_try_start_write (handle);


  if (request->response_len < request->request_len)
    pull_enqueue_request (handle,
                          request->request_offset + request->response_len,
                          request->request_len - request->response_len);
  else if (handle->max_req == 0)
    pull_try_finish (handle);
  else
    {


      if (handle->offset > handle->size)
        handle->max_req = 1;
      else if (handle->max_req < PULL_MAX_REQUESTS)
        handle->max_req++;

      while (handle->num_req < handle->max_req)
        pull_enqueue_next_request (handle);
    }

  pull_request_free (request);
}
