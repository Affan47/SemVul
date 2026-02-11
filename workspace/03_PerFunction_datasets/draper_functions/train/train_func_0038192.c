infd_filesystem_storage_storage_remove_node(InfdStorage* storage,
                                            const gchar* identifier,
                                            const gchar* path,
                                            GError** error)
{
  InfdFilesystemStorage* fs_storage;
  InfdFilesystemStoragePrivate* priv;
  gchar* converted_name;
  gchar* disk_name;
  gchar* full_name;
#ifdef G_OS_WIN32
  gchar* sep;
#endif
  gboolean ret;

  fs_storage = INFD_FILESYSTEM_STORAGE(storage);
  priv = INFD_FILESYSTEM_STORAGE_PRIVATE(fs_storage);

  if(infd_filesystem_storage_verify_path(path, error) == FALSE)
    return FALSE;

  converted_name = g_filename_from_utf8(path, -1, NULL, NULL, error);
  if(converted_name == NULL)
    return FALSE;

#ifdef G_OS_WIN32


  for(sep = converted_name; *sep != '\0'; ++sep)
    if(*sep == '/')
      *sep = '\\';
#endif

  if(identifier != NULL)
  {
    disk_name = g_strconcat(converted_name, ".", identifier, NULL);
    g_free(converted_name);
  }
  else
  {
    disk_name = converted_name;
  }

  full_name = g_build_filename(priv->root_directory, disk_name, NULL);
  g_free(disk_name);

  ret = infd_filesystem_storage_remove_rec(full_name, error);
  g_free(full_name);

  return ret;
}
