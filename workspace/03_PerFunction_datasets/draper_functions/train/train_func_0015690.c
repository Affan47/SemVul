try_seek_on_write (GVfsBackend *backend,
                   GVfsJobSeekWrite *job,
                   GVfsBackendHandle handle,
                   goffset    offset,
                   GSeekType  type)
{
  GVfsBackendAfp *afp_backend = G_VFS_BACKEND_AFP (backend);
  AfpHandle *afp_handle = (AfpHandle *)handle;

  if (afp_handle->type == AFP_HANDLE_TYPE_REPLACE_FILE_DIRECT ||
      job->seek_type != G_SEEK_END)
  {
    switch (job->seek_type)
    {
      case G_SEEK_CUR:
        afp_handle->offset += job->requested_offset;
        break;
      case G_SEEK_SET:
        afp_handle->offset = job->requested_offset;
        break;
      case G_SEEK_END:
        afp_handle->offset = afp_handle->size + job->requested_offset;
        break;
    }

    if (afp_handle->offset < 0)
      afp_handle->offset = 0;

    g_vfs_job_seek_write_set_offset (job, afp_handle->offset);
    g_vfs_job_succeeded (G_VFS_JOB (job));
  }

  else
  {
    g_vfs_afp_volume_get_fork_parms (afp_backend->volume, afp_handle->fork_refnum,
                                     AFP_FILE_BITMAP_EXT_DATA_FORK_LEN_BIT,
                                     G_VFS_JOB (job)->cancellable, seek_on_write_cb, job);
  }

  return TRUE;
}
