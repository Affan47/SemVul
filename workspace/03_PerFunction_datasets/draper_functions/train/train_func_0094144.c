error_550_is_directory (GVfsFtpTask *task, gpointer file)
{
  GFileInfo *info;


  info = g_vfs_ftp_dir_cache_lookup_file (task->backend->dir_cache, task, file, TRUE);
  if (info && g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY)
    {
      g_object_unref (info);
      g_set_error_literal (&task->error, G_IO_ERROR,
                           G_IO_ERROR_IS_DIRECTORY,
                           _("File is directory"));
      return;
    }
  else if (info)
    g_object_unref (info);


  g_vfs_ftp_task_clear_error (task);
}
