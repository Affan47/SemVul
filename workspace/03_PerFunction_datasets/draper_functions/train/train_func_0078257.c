gst_flv_demux_set_index (GstElement * element, GstIndex * index)
{
  GstFlvDemux *demux = GST_FLV_DEMUX (element);

  GST_OBJECT_LOCK (demux);
  if (demux->index)
    gst_object_unref (demux->index);
  if (index) {
    demux->index = gst_object_ref (index);
    demux->own_index = FALSE;
  } else
    demux->index = NULL;

  GST_OBJECT_UNLOCK (demux);

  if (index)
    gst_index_get_writer_id (index, GST_OBJECT (element), &demux->index_id);
  GST_DEBUG_OBJECT (demux, "Set index %" GST_PTR_FORMAT, demux->index);

}
