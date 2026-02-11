gst_flups_demux_mark_discont (GstFluPSDemux * demux, gboolean discont,
    gboolean need_segment)
{
  gint i, count = demux->found_count;


  for (i = 0; i < count; i++) {
    GstFluPSStream *stream = demux->streams_found[i];

    if (G_LIKELY (stream)) {
      stream->discont |= discont;
      stream->need_segment |= need_segment;
      demux->adjust_segment |= need_segment;
      GST_DEBUG_OBJECT (demux, "marked stream as discont %d, need_segment %d",
          stream->discont, stream->need_segment);
    }
  }
}
