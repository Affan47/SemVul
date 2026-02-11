mxf_metadata_cdci_picture_essence_descriptor_to_structure (MXFMetadataBase * m)
{
  GstStructure *ret =
      MXF_METADATA_BASE_CLASS
      (mxf_metadata_cdci_picture_essence_descriptor_parent_class)->to_structure
      (m);
  MXFMetadataCDCIPictureEssenceDescriptor *self =
      MXF_METADATA_CDCI_PICTURE_ESSENCE_DESCRIPTOR (m);

  if (self->component_depth != 0)
    gst_structure_id_set (ret, MXF_QUARK (COMPONENT_DEPTH), G_TYPE_UINT,
        self->component_depth, NULL);

  if (self->horizontal_subsampling != 0)
    gst_structure_id_set (ret, MXF_QUARK (HORIZONTAL_SUBSAMPLING), G_TYPE_UINT,
        self->horizontal_subsampling, NULL);

  if (self->vertical_subsampling != 0)
    gst_structure_id_set (ret, MXF_QUARK (VERTICAL_SUBSAMPLING), G_TYPE_UINT,
        self->vertical_subsampling, NULL);

  if (self->color_siting != 255)
    gst_structure_id_set (ret, MXF_QUARK (COLOR_SITING), G_TYPE_UCHAR,
        self->color_siting, NULL);

  gst_structure_id_set (ret, MXF_QUARK (REVERSED_BYTE_ORDER), G_TYPE_BOOLEAN,
      self->reversed_byte_order, NULL);

  if (self->padding_bits != 0)
    gst_structure_id_set (ret, MXF_QUARK (PADDING_BITS), G_TYPE_INT,
        self->padding_bits, NULL);

  if (self->alpha_sample_depth != 0)
    gst_structure_id_set (ret, MXF_QUARK (ALPHA_SAMPLE_DEPTH), G_TYPE_UINT,
        self->alpha_sample_depth, NULL);

  if (self->black_ref_level != 0)
    gst_structure_id_set (ret, MXF_QUARK (BLACK_REF_LEVEL), G_TYPE_UINT,
        self->black_ref_level, NULL);

  if (self->white_ref_level != 0)
    gst_structure_id_set (ret, MXF_QUARK (WHITE_REF_LEVEL), G_TYPE_UINT,
        self->white_ref_level, NULL);

  if (self->color_range != 0)
    gst_structure_id_set (ret, MXF_QUARK (COLOR_RANGE), G_TYPE_UINT,
        self->color_range, NULL);

  return ret;
}
