mxf_metadata_sequence_write_tags (MXFMetadataBase * m, MXFPrimerPack * primer)
{
  MXFMetadataSequence *self = MXF_METADATA_SEQUENCE (m);
  GList *ret =
      MXF_METADATA_BASE_CLASS (mxf_metadata_sequence_parent_class)->write_tags
      (m, primer);
  MXFLocalTag *t;

  t = g_slice_new0 (MXFLocalTag);
  memcpy (&t->ul, MXF_UL (DATA_DEFINITION), 16);
  t->size = 16;
  t->data = g_slice_alloc (t->size);
  t->g_slice = TRUE;
  memcpy (t->data, &self->data_definition, 16);
  mxf_primer_pack_add_mapping (primer, 0x0201, &t->ul);
  ret = g_list_prepend (ret, t);

  t = g_slice_new0 (MXFLocalTag);
  memcpy (&t->ul, MXF_UL (DURATION), 16);
  t->size = 8;
  t->data = g_slice_alloc (t->size);
  t->g_slice = TRUE;
  GST_WRITE_UINT64_BE (t->data, self->duration);
  mxf_primer_pack_add_mapping (primer, 0x0202, &t->ul);
  ret = g_list_prepend (ret, t);

  if (self->structural_components) {
    guint i;
    t = g_slice_new0 (MXFLocalTag);
    memcpy (&t->ul, MXF_UL (STRUCTURAL_COMPONENTS), 16);
    t->size = 8 + 16 * self->n_structural_components;
    t->data = g_slice_alloc0 (t->size);
    t->g_slice = TRUE;

    GST_WRITE_UINT32_BE (t->data, self->n_structural_components);
    GST_WRITE_UINT32_BE (t->data + 4, 16);
    for (i = 0; i < self->n_structural_components; i++) {
      if (!self->structural_components[i])
        continue;

      memcpy (t->data + 8 + i * 16,
          &MXF_METADATA_BASE (self->structural_components[i])->instance_uid,
          16);
    }

    mxf_primer_pack_add_mapping (primer, 0x1001, &t->ul);
    ret = g_list_prepend (ret, t);
  }

  return ret;
}
