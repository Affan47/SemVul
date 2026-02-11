do_move (GVfsBackend *backend,
         GVfsJobMove *job,
         const char *source,
         const char *destination,
         GFileCopyFlags flags,
         GFileProgressCallback progress_callback,
         gpointer progress_callback_data)
{
  GVfsBackendFtp *ftp = G_VFS_BACKEND_FTP (backend);
  GVfsFtpTask task = G_VFS_FTP_TASK_INIT (ftp, G_VFS_JOB (job));
  GVfsFtpFile *srcfile, *destfile;
  static const GVfsFtpErrorFunc rnfr_handlers[] = { error_550_permission_or_not_found,
                                                    NULL };


  if (flags & G_FILE_COPY_BACKUP)
    {

      g_set_error_literal (&task.error,
                           G_IO_ERROR,
                           G_IO_ERROR_CANT_CREATE_BACKUP,
                           _("backups not supported yet"));
      g_vfs_ftp_task_done (&task);
      return;
    }

  srcfile = g_vfs_ftp_file_new_from_gvfs (ftp, source);
  destfile = g_vfs_ftp_file_new_from_gvfs (ftp, destination);
  if (g_vfs_ftp_task_try_cd (&task, destfile))
    {
      char *basename = g_path_get_basename (source);
      GVfsFtpFile *real = g_vfs_ftp_file_new_child (destfile, basename, &task.error);

      g_free (basename);
      if (real == NULL)
        {
          goto out;
        }
      else
        {
          g_vfs_ftp_file_free (destfile);
          destfile = real;
        }
    }

  if (!(flags & G_FILE_COPY_OVERWRITE))
    {
      GFileInfo *info = g_vfs_ftp_dir_cache_lookup_file (ftp->dir_cache,
                                                         &task,
                                                         destfile,
                                                         FALSE);

      if (info)
        {
          g_object_unref (info);
          g_set_error_literal (&task.error,
                	       G_IO_ERROR,
                               G_IO_ERROR_EXISTS,
                	       _("Target file already exists"));
          goto out;
        }
    }


  if (!g_vfs_ftp_task_send_and_check (&task,
                                 G_VFS_FTP_PASS_300 | G_VFS_FTP_FAIL_200,
                                 rnfr_handlers,
                                 srcfile,
                                 NULL,
                                 "RNFR %s", g_vfs_ftp_file_get_ftp_path (srcfile)))
    goto out;

  g_vfs_ftp_task_send (&task,
                       0,
                       "RNTO %s", g_vfs_ftp_file_get_ftp_path (destfile));

  g_vfs_ftp_dir_cache_purge_file (ftp->dir_cache, srcfile);
  g_vfs_ftp_dir_cache_purge_file (ftp->dir_cache, destfile);
out:
  g_vfs_ftp_file_free (srcfile);
  g_vfs_ftp_file_free (destfile);

  g_vfs_ftp_task_done (&task);
}
