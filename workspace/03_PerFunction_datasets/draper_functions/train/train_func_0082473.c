infd_filesystem_storage_set_property(GObject* object,
                                     guint prop_id,
                                     const GValue* value,
                                     GParamSpec* pspec)
{
  InfdFilesystemStorage* storage;
  InfdFilesystemStoragePrivate* priv;

  storage = INFD_FILESYSTEM_STORAGE(object);
  priv = INFD_FILESYSTEM_STORAGE_PRIVATE(storage);

  switch(prop_id)
  {
  case PROP_ROOT_DIRECTORY:
    infd_filesystem_storage_set_root_directory(
      storage,
      g_value_get_string(value)
    );

    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}
