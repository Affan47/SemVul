send_reply (GVfsJob *job)
{
  GVfsJobCloseRead *op_job = G_VFS_JOB_CLOSE_READ (job);

  g_debug ("job_close_read send reply\n");

  if (job->failed)
    g_vfs_channel_send_error (G_VFS_CHANNEL (op_job->channel), job->error);
  else
    g_vfs_read_channel_send_closed (op_job->channel);
}
