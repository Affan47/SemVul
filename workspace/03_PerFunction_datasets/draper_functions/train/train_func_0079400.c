run (GVfsJob *job)
{
  GVfsJobSetAttribute *op_job = G_VFS_JOB_SET_ATTRIBUTE (job);
  GVfsBackendClass *class = G_VFS_BACKEND_GET_CLASS (op_job->backend);

  if (class->set_attribute == NULL)
    {
      g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED,
			_("Operation not supported by backend"));
      return;
    }

  class->set_attribute (op_job->backend,
			op_job,
			op_job->filename,
			op_job->attribute,
			op_job->type,
			_g_dbus_attribute_as_pointer (op_job->type, &op_job->value),
			op_job->flags);
}
