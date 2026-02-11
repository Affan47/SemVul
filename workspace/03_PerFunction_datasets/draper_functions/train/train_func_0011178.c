try_close_write (GVfsBackend *backend,
                 GVfsJobCloseWrite *job,
                 GVfsBackendHandle handle)
{
  GVfsBackendAfp *afp_backend = G_VFS_BACKEND_AFP (backend);
  AfpHandle *afp_handle = (AfpHandle *)handle;

  if (afp_handle->type == AFP_HANDLE_TYPE_REPLACE_FILE_TEMP)
  {
    g_vfs_afp_volume_exchange_files (afp_backend->volume, afp_handle->filename,
                                     afp_handle->tmp_filename,
                                     G_VFS_JOB (job)->cancellable,
                                     close_replace_exchange_files_cb, job);
  }
  else if (afp_handle->type == AFP_HANDLE_TYPE_REPLACE_FILE_DIRECT)
  {
    g_vfs_afp_volume_set_fork_size (afp_backend->volume, afp_handle->fork_refnum,
                                    afp_handle->size, G_VFS_JOB (job)->cancellable,
                                    close_replace_set_fork_size_cb, job);
  }
  else
  {

    g_vfs_afp_volume_get_fork_parms (afp_backend->volume, afp_handle->fork_refnum,
                                     AFP_FILE_BITMAP_MOD_DATE_BIT,
                                     G_VFS_JOB (job)->cancellable,
                                     close_write_get_fork_parms_cb, job);
  }

  return TRUE;
}
