copy_copy_file_cb (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  GVfsAfpVolume *volume = G_VFS_AFP_VOLUME (source_object);
  GVfsJobCopy *job = G_VFS_JOB_COPY (user_data);

  GError *err = NULL;

  if (!g_vfs_afp_volume_copy_file_finish (volume, res, &err))
  {
    g_vfs_job_failed_from_error (G_VFS_JOB (job), err);
    g_error_free (err);
    return;
  }

  g_vfs_job_succeeded (G_VFS_JOB (job));
}
