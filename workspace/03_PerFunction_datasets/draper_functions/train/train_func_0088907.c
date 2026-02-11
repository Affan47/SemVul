gst_avi_demux_add_assoc (GstAviDemux * avi, GstAviStream * stream,
    GstClockTime timestamp, guint64 offset, gboolean keyframe)
{

  if (G_UNLIKELY (avi->element_index && avi->seekable)) {
    GST_LOG_OBJECT (avi, "adding association %" GST_TIME_FORMAT "-> %"
        G_GUINT64_FORMAT, GST_TIME_ARGS (timestamp), offset);
    gst_index_add_association (avi->element_index, avi->index_id,
        keyframe ? GST_ASSOCIATION_FLAG_KEY_UNIT :
        GST_ASSOCIATION_FLAG_DELTA_UNIT, GST_FORMAT_TIME, timestamp,
        GST_FORMAT_BYTES, offset, NULL);

    gst_index_add_association (avi->element_index, stream->index_id,
        keyframe ? GST_ASSOCIATION_FLAG_KEY_UNIT :
        GST_ASSOCIATION_FLAG_DELTA_UNIT, GST_FORMAT_TIME, timestamp,
        GST_FORMAT_BYTES, offset, GST_FORMAT_DEFAULT, stream->current_entry,
        NULL);
  }
}
