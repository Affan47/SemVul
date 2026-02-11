open_stat_reply (GVfsBackendSftp *backend,
                 int reply_type,
                 GDataInputStream *reply,
                 guint32 len,
                 GVfsJob *job,
                 gpointer user_data)
{
  if (g_vfs_job_is_finished (job))
    {

      return;
    }

  if (reply_type == SSH_FXP_ATTRS)
    {
      GFileType type;
      GFileInfo *info = g_file_info_new ();

      parse_attributes (backend, info, NULL,
                        reply, NULL);
      type = g_file_info_get_file_type (info);
      g_object_unref (info);

      if (type == G_FILE_TYPE_DIRECTORY)
        {
          g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_IS_DIRECTORY,
                            _("File is directory"));
          return;
        }
    }

  if (GPOINTER_TO_INT (G_VFS_JOB(job)->backend_data) == 1)
    {

      g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_FAILED,
                        _("Failure"));
    }
}
