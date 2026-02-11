g_vfs_job_set_attribute_finalize (GObject *object)
{
  GVfsJobSetAttribute *job;

  job = G_VFS_JOB_SET_ATTRIBUTE (object);

  g_free (job->filename);
  g_free (job->attribute);
  _g_dbus_attribute_value_destroy (job->type,
				   &job->value);

  if (G_OBJECT_CLASS (g_vfs_job_set_attribute_parent_class)->finalize)
    (*G_OBJECT_CLASS (g_vfs_job_set_attribute_parent_class)->finalize) (object);
}
