try_set_attribute (GVfsBackend *backend,
		   GVfsJobSetAttribute *job,
		   const char *filename,
		   const char *attribute,
		   GFileAttributeType type,
		   gpointer value_p,
		   GFileQueryInfoFlags flags)
{
  GVfsBackendSftp *op_backend = G_VFS_BACKEND_SFTP (backend);
  GDataOutputStream *command;

  if (strcmp (attribute, G_FILE_ATTRIBUTE_UNIX_MODE) != 0)
    {
      g_vfs_job_failed (G_VFS_JOB (job),
			G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED,
			_("Operation unsupported"));
      return TRUE;
    }

  if (type != G_FILE_ATTRIBUTE_TYPE_UINT32)
    {
      g_vfs_job_failed (G_VFS_JOB (job),
                        G_IO_ERROR,
                        G_IO_ERROR_INVALID_ARGUMENT,
                        "%s",
                        _("Invalid attribute type (uint32 expected)"));
      return TRUE;
    }

  command = new_command_stream (op_backend,
                                SSH_FXP_SETSTAT);
  put_string (command, filename);
  g_data_output_stream_put_uint32 (command, SSH_FILEXFER_ATTR_PERMISSIONS, NULL, NULL);
  g_data_output_stream_put_uint32 (command, (*(guint32 *)value_p) & 0777, NULL, NULL);
  queue_command_stream_and_free (op_backend, command, set_attribute_reply, G_VFS_JOB (job), NULL);

  return TRUE;
}
