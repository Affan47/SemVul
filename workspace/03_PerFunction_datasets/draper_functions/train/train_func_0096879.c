append_to_get_fork_parms_cb (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  GVfsAfpVolume *volume = G_VFS_AFP_VOLUME (source_object);
  GVfsJobOpenForWrite *job = G_VFS_JOB_OPEN_FOR_WRITE (user_data);
  AfpHandle *afp_handle = (AfpHandle *)job->backend_handle;

  GFileInfo *info;
  GError *err = NULL;
  goffset size;

  info = g_vfs_afp_volume_get_fork_parms_finish (volume, res, &err);
  if (!info)
  {
    g_vfs_job_failed_from_error (G_VFS_JOB (job), err);
    g_error_free (err);
    afp_handle_free (afp_handle);
    return;
  }

  size = g_file_info_get_size (info);
  g_object_unref (info);

  afp_handle->offset = size;
  g_vfs_job_open_for_write_set_initial_offset (job, size);
  g_vfs_job_open_for_write_set_can_seek (job, TRUE);
  g_vfs_job_open_for_write_set_can_truncate (job, TRUE);

  g_vfs_job_succeeded (G_VFS_JOB (job));
}
