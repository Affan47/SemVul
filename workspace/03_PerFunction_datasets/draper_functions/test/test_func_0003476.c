mxf_dms1_device_parameters_resolve (MXFMetadataBase * m, GHashTable * metadata)
{
  MXFDMS1DeviceParameters *self = MXF_DMS1_DEVICE_PARAMETERS (m);
  MXFMetadataBase *current = NULL;
  guint i;

  if (self->name_value_sets)
    memset (self->name_value_sets, 0,
        sizeof (gpointer) * self->n_name_value_sets);
  else
    self->name_value_sets =
        g_new0 (MXFDMS1NameValue *, self->n_name_value_sets);

  for (i = 0; i < self->n_name_value_sets; i++) {
    current = g_hash_table_lookup (metadata, &self->name_value_sets_uids[i]);
    if (current && MXF_IS_DMS1_NAME_VALUE (current)) {
      self->name_value_sets[i] = MXF_DMS1_NAME_VALUE (current);
    }
  }

  return
      MXF_METADATA_BASE_CLASS (mxf_dms1_device_parameters_parent_class)->resolve
      (m, metadata);
}
