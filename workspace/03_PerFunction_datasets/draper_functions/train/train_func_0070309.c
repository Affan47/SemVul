gst_qtdemux_pull_atom (GstQTDemux * qtdemux, guint64 offset, guint64 size,
    GstBuffer ** buf)
{
  GstFlowReturn flow;

  if (G_UNLIKELY (size == 0)) {
    GstFlowReturn ret;
    GstBuffer *tmp = NULL;

    ret = gst_qtdemux_pull_atom (qtdemux, offset, sizeof (guint32), &tmp);
    if (ret != GST_FLOW_OK)
      return ret;

    size = QT_UINT32 (GST_BUFFER_DATA (tmp));
    GST_DEBUG_OBJECT (qtdemux, "size 0x%08" G_GINT64_MODIFIER "x", size);

    gst_buffer_unref (tmp);
  }


  if (G_UNLIKELY (size > QTDEMUX_MAX_ATOM_SIZE)) {
    if (qtdemux->state != QTDEMUX_STATE_MOVIE && qtdemux->got_moov) {


      GST_WARNING_OBJECT (qtdemux, "atom has bogus size %" G_GUINT64_FORMAT,
          size);
      return GST_FLOW_UNEXPECTED;
    } else {
      GST_ELEMENT_ERROR (qtdemux, STREAM, DEMUX,
          (_("This file is invalid and cannot be played.")),
          ("atom has bogus size %" G_GUINT64_FORMAT, size));
      return GST_FLOW_ERROR;
    }
  }

  flow = gst_pad_pull_range (qtdemux->sinkpad, offset, size, buf);

  if (G_UNLIKELY (flow != GST_FLOW_OK))
    return flow;


  if (G_UNLIKELY (GST_BUFFER_SIZE (*buf) < size)) {
    GST_WARNING_OBJECT (qtdemux, "short read: %u < %" G_GUINT64_FORMAT,
        GST_BUFFER_SIZE (*buf), size);
    gst_buffer_unref (*buf);
    *buf = NULL;
    return GST_FLOW_UNEXPECTED;
  }

  return flow;
}
