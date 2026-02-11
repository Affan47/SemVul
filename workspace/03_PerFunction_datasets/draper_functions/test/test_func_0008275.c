g_vfs_job_error_finalize (GObject *object)
{
  GVfsJobError *job;

  job = G_VFS_JOB_ERROR (object);
  g_object_unref (job->channel);
  g_error_free (job->error);

  if (G_OBJECT_CLASS (g_vfs_job_error_parent_class)->finalize)
    (*G_OBJECT_CLASS (g_vfs_job_error_parent_class)->finalize) (object);
}
