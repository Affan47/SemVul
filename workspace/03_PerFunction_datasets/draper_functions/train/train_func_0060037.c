infd_storage_remove_node(InfdStorage* storage,
                         const gchar* identifier,
                         const gchar* path,
                         GError** error)
{
  InfdStorageIface* iface;

  g_return_val_if_fail(INFD_IS_STORAGE(storage), FALSE);
  g_return_val_if_fail(path != NULL, FALSE);

  iface = INFD_STORAGE_GET_IFACE(storage);
  g_return_val_if_fail(iface->remove_node != NULL, FALSE);

  return iface->remove_node(storage, identifier, path, error);
}
