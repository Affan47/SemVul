gst_avi_demux_stream_init_push (GstAviDemux * avi)
{
  if (gst_adapter_available (avi->adapter) >= 12) {
    GstBuffer *tmp;

    tmp = gst_adapter_take_buffer (avi->adapter, 12);

    GST_DEBUG ("Parsing avi header");
    if (!gst_avi_demux_parse_file_header (GST_ELEMENT_CAST (avi), tmp)) {
      return GST_FLOW_ERROR;
    }
    GST_DEBUG ("header ok");
    avi->offset += 12;

    avi->state = GST_AVI_DEMUX_HEADER;
  }
  return GST_FLOW_OK;
}
