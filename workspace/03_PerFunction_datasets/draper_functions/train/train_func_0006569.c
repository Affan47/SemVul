mxf_metadata_handle_tag (MXFMetadataBase * metadata, MXFPrimerPack * primer,
    guint16 tag, const guint8 * tag_data, guint tag_size)
{
#ifndef GST_DISABLE_GST_DEBUG
  gchar str[48];
#endif
  MXFMetadata *self = MXF_METADATA (metadata);
  gboolean ret = TRUE;

  switch (tag) {
    case 0x3c0a:
      if (tag_size != 16)
        goto error;
      memcpy (&self->parent.instance_uid, tag_data, 16);
      GST_DEBUG ("  instance uid = %s",
          mxf_uuid_to_string (&self->parent.instance_uid, str));
      break;
    case 0x0102:
      if (tag_size != 16)
        goto error;
      memcpy (&self->parent.generation_uid, tag_data, 16);
      GST_DEBUG ("  generation uid = %s",
          mxf_uuid_to_string (&self->parent.generation_uid, str));
      break;
    default:
      ret =
          MXF_METADATA_BASE_CLASS (mxf_metadata_parent_class)->handle_tag
          (metadata, primer, tag, tag_data, tag_size);
      break;
  }

  return ret;

error:

  GST_ERROR ("Invalid metadata local tag 0x%04x of size %u", tag, tag_size);

  return FALSE;
}
