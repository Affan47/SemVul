gst_mxf_demux_handle_descriptive_metadata (GstMXFDemux * demux,
    const MXFUL * key, GstBuffer * buffer)
{
  guint32 type;
  guint8 scheme;
  GstFlowReturn ret = GST_FLOW_OK;
  MXFDescriptiveMetadata *m = NULL, *old = NULL;

  scheme = GST_READ_UINT8 (key->u + 12);
  type = GST_READ_UINT24_BE (key->u + 13);

  GST_DEBUG_OBJECT (demux,
      "Handling descriptive metadata of size %u at offset %"
      G_GUINT64_FORMAT " with scheme 0x%02x and type 0x%06x",
      GST_BUFFER_SIZE (buffer), demux->offset, scheme, type);

  if (G_UNLIKELY (!demux->current_partition)) {
    GST_ERROR_OBJECT (demux, "Partition pack doesn't exist");
    return GST_FLOW_ERROR;
  }

  if (G_UNLIKELY (!demux->current_partition->primer.mappings)) {
    GST_ERROR_OBJECT (demux, "Primer pack doesn't exists");
    return GST_FLOW_ERROR;
  }

  if (demux->current_partition->parsed_metadata) {
    GST_DEBUG_OBJECT (demux, "Metadata of this partition was already parsed");
    return GST_FLOW_OK;
  }

  m = mxf_descriptive_metadata_new (scheme, type,
      &demux->current_partition->primer, demux->offset,
      GST_BUFFER_DATA (buffer), GST_BUFFER_SIZE (buffer));

  if (!m) {
    GST_WARNING_OBJECT (demux,
        "Unknown or unhandled descriptive metadata of scheme 0x%02x and type 0x%06x",
        scheme, type);
    return GST_FLOW_OK;
  }

  old =
      g_hash_table_lookup (demux->metadata,
      &MXF_METADATA_BASE (m)->instance_uid);

  if (old && G_TYPE_FROM_INSTANCE (old) != G_TYPE_FROM_INSTANCE (m)) {
#ifndef GST_DISABLE_GST_DEBUG
    gchar str[48];
#endif

    GST_DEBUG_OBJECT (demux,
        "Metadata with instance uid %s already exists and has different type '%s',"
        " expected '%s'",
        mxf_uuid_to_string (&MXF_METADATA_BASE (m)->instance_uid, str),
        g_type_name (G_TYPE_FROM_INSTANCE (old)),
        g_type_name (G_TYPE_FROM_INSTANCE (m)));
    gst_mini_object_unref (GST_MINI_OBJECT (m));
    return GST_FLOW_ERROR;
  } else if (old
      && MXF_METADATA_BASE (old)->offset >= MXF_METADATA_BASE (m)->offset) {
#ifndef GST_DISABLE_GST_DEBUG
    gchar str[48];
#endif

    GST_DEBUG_OBJECT (demux,
        "Metadata with instance uid %s already exists and is newer",
        mxf_uuid_to_string (&MXF_METADATA_BASE (m)->instance_uid, str));
    gst_mini_object_unref (GST_MINI_OBJECT (m));
    return GST_FLOW_OK;
  }

  g_static_rw_lock_writer_lock (&demux->metadata_lock);

  demux->update_metadata = TRUE;
  gst_mxf_demux_reset_linked_metadata (demux);

  g_hash_table_replace (demux->metadata, &MXF_METADATA_BASE (m)->instance_uid,
      m);

  g_static_rw_lock_writer_unlock (&demux->metadata_lock);

  return ret;
}
