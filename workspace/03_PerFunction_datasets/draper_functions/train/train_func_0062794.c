g_vfs_ftp_file_copy (const GVfsFtpFile *file)
{
  GVfsFtpFile *copy;

  g_return_val_if_fail (file != NULL, NULL);

  copy = g_slice_new (GVfsFtpFile);
  copy->backend = g_object_ref (file->backend);
  copy->ftp_path = g_strdup (file->ftp_path);
  copy->gvfs_path = g_strdup (file->gvfs_path);

  return copy;
}
