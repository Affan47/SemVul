gst_matroska_demux_chain (GstPad * pad, GstBuffer * buffer)
{
  GstMatroskaDemux *demux = GST_MATROSKA_DEMUX (GST_PAD_PARENT (pad));
  guint available;
  GstFlowReturn ret = GST_FLOW_OK;
  guint needed = 0;
  guint32 id;
  guint64 length;

  if (G_UNLIKELY (GST_BUFFER_IS_DISCONT (buffer))) {
    GST_DEBUG_OBJECT (demux, "got DISCONT");
    gst_adapter_clear (demux->common.adapter);
    GST_OBJECT_LOCK (demux);
    gst_matroska_read_common_reset_streams (&demux->common,
        GST_CLOCK_TIME_NONE, FALSE);
    GST_OBJECT_UNLOCK (demux);
  }

  gst_adapter_push (demux->common.adapter, buffer);
  buffer = NULL;

next:
  available = gst_adapter_available (demux->common.adapter);

  ret = gst_matroska_read_common_peek_id_length_push (&demux->common,
      GST_ELEMENT_CAST (demux), &id, &length, &needed);
  if (G_UNLIKELY (ret != GST_FLOW_OK && ret != GST_FLOW_UNEXPECTED))
    return ret;

  GST_LOG_OBJECT (demux, "Offset %" G_GUINT64_FORMAT ", Element id 0x%x, "
      "size %" G_GUINT64_FORMAT ", needed %d, available %d",
      demux->common.offset, id, length, needed, available);

  if (needed > available)
    return GST_FLOW_OK;

  ret = gst_matroska_demux_parse_id (demux, id, length, needed);
  if (ret == GST_FLOW_UNEXPECTED) {

    return GST_FLOW_OK;
  } else if (ret != GST_FLOW_OK) {
    return ret;
  } else
    goto next;
}
