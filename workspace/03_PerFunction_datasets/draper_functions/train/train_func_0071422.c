gst_flups_demux_get_stream (GstFluPSDemux * demux, gint id, gint type)
{
  GstFluPSStream *stream = demux->streams[id];

  if (stream == NULL && !demux->disable_stream_creation) {
    if (!(stream = gst_flups_demux_create_stream (demux, id, type)))
      goto unknown_stream;

    GST_DEBUG_OBJECT (demux, "adding pad for stream id 0x%02x type 0x%02x", id,
        type);

    gst_pad_set_active (stream->pad, TRUE);
    gst_element_add_pad (GST_ELEMENT (demux), stream->pad);

    demux->streams[id] = stream;
  }
  return stream;


unknown_stream:
  {
    GST_DEBUG_OBJECT (demux, "unknown stream id 0x%02x type 0x%02x", id, type);
    return NULL;
  }
}
