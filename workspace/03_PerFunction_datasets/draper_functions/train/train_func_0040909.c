mxf_metadata_essence_container_data_resolve (MXFMetadataBase * m,
    GHashTable * metadata)
{
  MXFMetadataEssenceContainerData *self =
      MXF_METADATA_ESSENCE_CONTAINER_DATA (m);
  MXFMetadataBase *current = NULL;
  GHashTableIter iter;
#ifndef GST_DISABLE_GST_DEBUG
  gchar str[96];
#endif

  g_hash_table_iter_init (&iter, metadata);

  while (g_hash_table_iter_next (&iter, NULL, (gpointer) & current)) {
    if (MXF_IS_METADATA_SOURCE_PACKAGE (current)) {
      MXFMetadataSourcePackage *package = MXF_METADATA_SOURCE_PACKAGE (current);

      if (mxf_umid_is_equal (&package->parent.package_uid,
              &self->linked_package_uid)) {
        if (mxf_metadata_base_resolve (current, metadata)) {
          self->linked_package = package;
        } else {
          GST_ERROR ("Couldn't resolve linked package %s",
              mxf_umid_to_string (&self->linked_package_uid, str));
        }
        break;
      }
    }
  }

  if (!self->linked_package) {
    GST_ERROR ("Couldn't resolve or find linked package %s",
        mxf_umid_to_string (&self->linked_package_uid, str));
    return FALSE;
  }

  return
      MXF_METADATA_BASE_CLASS
      (mxf_metadata_essence_container_data_parent_class)->resolve (m, metadata);
}
