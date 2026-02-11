g_vfs_job_move_new_handle (GVfsDBusMount *object,
                           GDBusMethodInvocation *invocation,
                           const gchar *arg_path1_data,
                           const gchar *arg_path2_data,
                           guint arg_flags,
                           const gchar *arg_progress_obj_path,
                           GVfsBackend *backend)
{
  GVfsJobMove *job;
  GVfsJobProgress *progress_job;

  if (g_vfs_backend_invocation_first_handler (object, invocation, backend))
    return TRUE;

  job = g_object_new (G_VFS_TYPE_JOB_MOVE,
                      "object", object,
                      "invocation", invocation,
                      NULL);
  progress_job = G_VFS_JOB_PROGRESS (job);

  job->source = g_strdup (arg_path1_data);
  job->destination = g_strdup (arg_path2_data);
  job->backend = backend;
  job->flags = arg_flags;
  if (strcmp (arg_progress_obj_path, "/org/gtk/vfs/void") != 0)
    progress_job->callback_obj_path = g_strdup (arg_progress_obj_path);
  progress_job->send_progress = progress_job->callback_obj_path != NULL;

  g_vfs_job_source_new_job (G_VFS_JOB_SOURCE (backend), G_VFS_JOB (job));
  g_object_unref (job);

  return TRUE;
}
