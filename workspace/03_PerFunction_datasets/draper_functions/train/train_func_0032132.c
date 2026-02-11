send_reply (GVfsJob *job)
{
  GVfsJobQueryInfoRead *op_job = G_VFS_JOB_QUERY_INFO_READ (job);

  if (job->failed)
    g_vfs_channel_send_error (G_VFS_CHANNEL (op_job->channel), job->error);
  else
    g_vfs_channel_send_info (G_VFS_CHANNEL (op_job->channel), op_job->file_info);
}
