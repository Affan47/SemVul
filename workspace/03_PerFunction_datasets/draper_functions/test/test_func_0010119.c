mxf_metadata_dm_segment_resolve (MXFMetadataBase * m, GHashTable * metadata)
{
  MXFMetadataDMSegment *self = MXF_METADATA_DM_SEGMENT (m);
  MXFMetadataBase *current = NULL;

  current = g_hash_table_lookup (metadata, &self->dm_framework_uid);
  if (current && MXF_IS_DESCRIPTIVE_METADATA_FRAMEWORK (current)) {
    if (mxf_metadata_base_resolve (current, metadata)) {
      self->dm_framework = MXF_DESCRIPTIVE_METADATA_FRAMEWORK (current);
    } else {
      GST_ERROR ("Couldn't resolve DM framework");
      return FALSE;
    }
  } else {
    GST_ERROR ("Couldn't find DM framework");
    return FALSE;
  }


  return
      MXF_METADATA_BASE_CLASS (mxf_metadata_dm_segment_parent_class)->resolve
      (m, metadata);
}
