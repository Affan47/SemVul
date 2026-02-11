mxf_metadata_dm_source_clip_write_tags (MXFMetadataBase * m,
    MXFPrimerPack * primer)
{
  MXFMetadataDMSourceClip *self = MXF_METADATA_DM_SOURCE_CLIP (m);
  GList *ret =
      MXF_METADATA_BASE_CLASS
      (mxf_metadata_dm_source_clip_parent_class)->write_tags (m, primer);
  MXFLocalTag *t;

  if (self->track_ids) {
    guint i;

    t = g_slice_new0 (MXFLocalTag);
    memcpy (&t->ul, MXF_UL (DM_SOURCECLIP_TRACK_IDS), 16);
    t->size = 8 + 4 * self->n_track_ids;
    t->data = g_slice_alloc (t->size);
    t->g_slice = TRUE;
    GST_WRITE_UINT32_BE (t->data, self->n_track_ids);
    GST_WRITE_UINT32_BE (t->data + 4, 4);
    for (i = 0; i < self->n_track_ids; i++)
      GST_WRITE_UINT32_BE (t->data + 8 + i * 4, self->track_ids[i]);
    mxf_primer_pack_add_mapping (primer, 0x6103, &t->ul);
    ret = g_list_prepend (ret, t);
  }

  return ret;
}
