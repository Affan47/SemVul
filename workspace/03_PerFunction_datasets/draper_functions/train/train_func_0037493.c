child_watch_cb (GPid     pid,
                gint     status,
                gpointer user_data)
{
  UDisksSpawnedJob *job = UDISKS_SPAWNED_JOB (user_data);
  gchar *buf;
  gsize buf_size;
  gboolean ret;

  if (g_io_channel_read_to_end (job->child_stdout_channel, &buf, &buf_size, NULL) == G_IO_STATUS_NORMAL)
    {
      g_string_append_len (job->child_stdout, buf, buf_size);
      g_free (buf);
    }
  if (g_io_channel_read_to_end (job->child_stderr_channel, &buf, &buf_size, NULL) == G_IO_STATUS_NORMAL)
    {
      g_string_append_len (job->child_stderr, buf, buf_size);
      g_free (buf);
    }


  g_object_ref (job);
  g_signal_emit (job,
                 signals[SPAWNED_JOB_COMPLETED_SIGNAL],
                 0,
                 NULL,
                 status,
                 job->child_stdout,
                 job->child_stderr,
                 &ret);
  job->child_pid = 0;
  job->child_watch_source = NULL;
  udisks_spawned_job_release_resources (job);
  g_object_unref (job);
}
