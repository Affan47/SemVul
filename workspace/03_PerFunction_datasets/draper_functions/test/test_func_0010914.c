g_vfs_ftp_file_new_from_ftp (GVfsBackendFtp *ftp, const char *ftp_path)
{
  GVfsFtpFile *file;

  g_return_val_if_fail (G_VFS_IS_BACKEND_FTP (ftp), NULL);
  g_return_val_if_fail (ftp_path != NULL, NULL);

  file = g_slice_new (GVfsFtpFile);
  file->backend = g_object_ref (ftp);
  file->ftp_path = g_strdup (ftp_path);
  file->gvfs_path = g_vfs_ftp_file_compute_gvfs_path (ftp_path);

  return file;
}
