g_vfs_job_progress_finalize (GObject *object)
{
  GVfsJobProgress *job;

  job = G_VFS_JOB_PROGRESS (object);

  g_free (job->callback_obj_path);
  g_clear_object (&job->progress_proxy);

  if (G_OBJECT_CLASS (g_vfs_job_progress_parent_class)->finalize)
    (*G_OBJECT_CLASS (g_vfs_job_progress_parent_class)->finalize) (object);
}
