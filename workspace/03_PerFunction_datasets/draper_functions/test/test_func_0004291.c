trash_backend_pull (GVfsBackend           *vfs_backend,
                    GVfsJobPull           *job,
                    const gchar           *source,
                    const gchar           *local_path,
                    GFileCopyFlags         flags,
                    gboolean               remove_source,
                    GFileProgressCallback  progress_callback,
                    gpointer               progress_callback_data)
{
  GVfsBackendTrash *backend = G_VFS_BACKEND_TRASH (vfs_backend);
  GError *error = NULL;

  if (source[1] == '\0')
    g_set_error_literal (&error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED,
                         _("The trash folder may not be deleted"));
  else
    {
      gboolean is_toplevel;
      TrashItem *item;
      GFile *real;

      real = trash_backend_get_file (backend, source, &item,
                                     &is_toplevel, &error);

      if (real)
        {
          if (remove_source && !is_toplevel)
            g_set_error_literal (&error, G_IO_ERROR, G_IO_ERROR_PERMISSION_DENIED,
                                 _("Items in the trash may not be modified"));

          else
            {
              GFile *destination;
              gboolean it_worked;

              destination = g_file_new_for_path (local_path);

              if (remove_source)
                it_worked = trash_item_restore (item, destination, flags, &error);
              else
                it_worked = g_file_copy (real, destination, flags,
                                         G_VFS_JOB (job)->cancellable,
                                         progress_callback, progress_callback_data, &error);

              g_object_unref (destination);

              if (it_worked)
                {
                  g_vfs_job_succeeded (G_VFS_JOB (job));
                  trash_item_unref (item);
                  g_object_unref (real);

                  return TRUE;
                }
            }

          trash_item_unref (item);
          g_object_unref (real);
        }

    }

  g_vfs_job_failed_from_error (G_VFS_JOB (job), error);
  g_error_free (error);

  return TRUE;
}
