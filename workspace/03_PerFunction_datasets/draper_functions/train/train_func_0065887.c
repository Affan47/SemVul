gst_mxf_demux_get_earliest_pad (GstMXFDemux * demux)
{
  guint i;
  GstClockTime earliest = GST_CLOCK_TIME_NONE;
  GstMXFDemuxPad *pad = NULL;

  for (i = 0; i < demux->src->len; i++) {
    GstMXFDemuxPad *p = g_ptr_array_index (demux->src, i);

    if (!p->eos && p->last_flow < earliest) {
      earliest = p->last_flow;
      pad = p;
    }
  }

  return pad;
}
