mxf_vc3_get_descriptor (GstPadTemplate * tmpl, GstCaps * caps,
    MXFEssenceElementWriteFunc * handler, gpointer * mapping_data)
{
  MXFMetadataCDCIPictureEssenceDescriptor *ret;
  GstStructure *s;

  s = gst_caps_get_structure (caps, 0);
  if (strcmp (gst_structure_get_name (s), "video/x-dnxhd") != 0) {
    GST_ERROR ("Invalid caps %" GST_PTR_FORMAT, caps);
    return NULL;
  }

  ret = (MXFMetadataCDCIPictureEssenceDescriptor *)
      g_object_new (MXF_TYPE_METADATA_CDCI_PICTURE_ESSENCE_DESCRIPTOR, NULL);

  memcpy (&ret->parent.parent.essence_container, &vc3_essence_container_ul, 16);

  if (!mxf_metadata_generic_picture_essence_descriptor_from_caps (&ret->parent,
          caps)) {
    g_object_unref (ret);
    return NULL;
  }

  *handler = mxf_vc3_write_func;

  return (MXFMetadataFileDescriptor *) ret;
}
