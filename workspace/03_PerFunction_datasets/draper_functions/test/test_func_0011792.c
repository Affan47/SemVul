mxf_metadata_dm_source_clip_to_structure (MXFMetadataBase * m)
{
  GstStructure *ret =
      MXF_METADATA_BASE_CLASS
      (mxf_metadata_dm_source_clip_parent_class)->to_structure (m);
  MXFMetadataDMSourceClip *self = MXF_METADATA_DM_SOURCE_CLIP (m);
  guint i;

  if (self->n_track_ids > 0) {
    GValue arr = { 0, }
    , val = {
    0,};

    g_value_init (&arr, GST_TYPE_ARRAY);

    for (i = 0; i < self->n_track_ids; i++) {
      g_value_init (&val, G_TYPE_UINT);

      g_value_set_uint (&val, self->track_ids[i]);
      gst_value_array_append_value (&arr, &val);
      g_value_unset (&val);
    }

    if (gst_value_array_get_size (&arr) > 0)
      gst_structure_id_set_value (ret, MXF_QUARK (TRACK_IDS), &arr);

    g_value_unset (&arr);
  }

  return ret;
}
