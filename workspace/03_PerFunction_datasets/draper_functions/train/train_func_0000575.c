do_copy (CopyData *copy_data)
{
  GVfsJobCopy *job = copy_data->job;
  GVfsBackendAfp *afp_backend = G_VFS_BACKEND_AFP (job->backend);

  GFileInfo *info;
  GError *err = NULL;

  gboolean source_is_dir;
  gboolean dest_exists;
  gboolean dest_is_dir;

  info = g_vfs_afp_volume_get_filedir_parms_finish (afp_backend->volume, copy_data->source_parms_res, &err);
  if (!info)
  {
    g_vfs_job_failed_from_error (G_VFS_JOB (job), err);
    g_error_free (err);
    goto done;
  }


  source_is_dir = g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY ? TRUE : FALSE;
  g_object_unref (info);

  info = g_vfs_afp_volume_get_filedir_parms_finish (afp_backend->volume, copy_data->dest_parms_res, &err);
  if (!info)
  {
    if (g_error_matches (err, G_IO_ERROR, G_IO_ERROR_NOT_FOUND))
    {
      g_clear_error (&err);
      dest_exists = FALSE;
    }
    else
    {
      g_vfs_job_failed_from_error (G_VFS_JOB (job), err);
      g_error_free (err);
      goto done;
    }
  }
  else
  {
    dest_exists = TRUE;
    dest_is_dir = g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY ? TRUE : FALSE;
    g_object_unref (info);
  }


  if (dest_exists)
  {
    if ((job->flags & G_FILE_COPY_OVERWRITE))
    {

      if (dest_is_dir)
      {
        if (source_is_dir)
          g_vfs_job_failed_literal (G_VFS_JOB (job), G_IO_ERROR, G_IO_ERROR_WOULD_MERGE,
                                    _("Can't copy directory over directory"));
        else
          g_vfs_job_failed_literal (G_VFS_JOB (job), G_IO_ERROR, G_IO_ERROR_IS_DIRECTORY,
                                    _("File is directory"));
        goto done;
      }
    }
    else
    {
      g_vfs_job_failed (G_VFS_JOB (job), G_IO_ERROR, G_IO_ERROR_EXISTS,
                        _("Target file already exists"));
      goto done;
    }
  }


  if (source_is_dir)
  {
    g_vfs_job_failed (G_VFS_JOB (job), G_IO_ERROR, G_IO_ERROR_WOULD_RECURSE,
                      _("Can't recursively copy directory"));
    goto done;
  }

  if (dest_exists)
  {
    g_vfs_afp_volume_delete (afp_backend->volume, job->destination,
                             G_VFS_JOB (job)->cancellable, copy_delete_cb, job);
  }
  else
  {
    g_vfs_afp_volume_copy_file (afp_backend->volume, job->source, job->destination,
                                G_VFS_JOB (job)->cancellable, copy_copy_file_cb, job);
  }

done:
  copy_data_free (copy_data);
  return;
}
