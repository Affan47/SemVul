rename_cb (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  GVfsAfpVolume *volume = G_VFS_AFP_VOLUME (source_object);
  GVfsJobSetDisplayName *job = G_VFS_JOB_SET_DISPLAY_NAME (user_data);

  GError *err = NULL;
  char *dirname, *newpath;

  if (!g_vfs_afp_volume_rename_finish (volume, res, &err))
  {
    g_vfs_job_failed_from_error (G_VFS_JOB (job), err);
    g_error_free (err);
    return;
  }

  dirname = g_path_get_dirname (job->filename);
  newpath = g_build_filename (dirname, job->display_name, NULL);
  g_vfs_job_set_display_name_set_new_path (job, newpath);

  g_free (dirname);
  g_free (newpath);

  g_vfs_job_succeeded (G_VFS_JOB (job));
}
