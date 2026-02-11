mxf_metadata_source_clip_handle_tag (MXFMetadataBase * metadata,
    MXFPrimerPack * primer, guint16 tag, const guint8 * tag_data,
    guint tag_size)
{
  MXFMetadataSourceClip *self = MXF_METADATA_SOURCE_CLIP (metadata);
  gboolean ret = TRUE;
#ifndef GST_DISABLE_GST_DEBUG
  gchar str[96];
#endif

  switch (tag) {
    case 0x1201:
      if (tag_size != 8)
        goto error;

      self->start_position = GST_READ_UINT64_BE (tag_data);
      GST_DEBUG ("  start position = %" G_GINT64_FORMAT, self->start_position);
      break;
    case 0x1101:
      if (tag_size != 32)
        goto error;

      memcpy (&self->source_package_id, tag_data, 32);
      GST_DEBUG ("  source package id = %s",
          mxf_umid_to_string (&self->source_package_id, str));
      break;
    case 0x1102:
      if (tag_size != 4)
        goto error;

      self->source_track_id = GST_READ_UINT32_BE (tag_data);
      GST_DEBUG ("  source track id = %u", self->source_track_id);
      break;
    default:
      ret =
          MXF_METADATA_BASE_CLASS
          (mxf_metadata_source_clip_parent_class)->handle_tag (metadata, primer,
          tag, tag_data, tag_size);
      break;
  }

  return ret;

error:

  GST_ERROR ("Invalid source clip local tag 0x%04x of size %u", tag, tag_size);

  return FALSE;
}
