gst_nuv_demux_stream_file_header (GstNuvDemux * nuv)
{
  GstFlowReturn res = GST_FLOW_OK;
  GstBuffer *file_header = NULL;

  res = gst_nuv_demux_read_bytes (nuv, 12, FALSE, &file_header);
  if (res != GST_FLOW_OK) {
    return res;
  } else {
    if (strncmp ((gchar *) file_header->data, "MythTVVideo", 11) ||
        strncmp ((gchar *) file_header->data, "NuppelVideo", 11)) {
      nuv->state = GST_NUV_DEMUX_HEADER_DATA;
    } else {
      GST_DEBUG_OBJECT (nuv, "error parsing file header");
      nuv->state = GST_NUV_DEMUX_INVALID_DATA;
      res = GST_FLOW_ERROR;
    }
  }
  if (file_header != NULL) {
    gst_buffer_unref (file_header);
  }
  return res;
}
