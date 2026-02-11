gst_ogg_demux_reset_streams (GstOggDemux * ogg)
{
  GstOggChain *chain;
  guint i;

  chain = ogg->current_chain;
  if (chain == NULL)
    return;

  for (i = 0; i < chain->streams->len; i++) {
    GstOggPad *stream = g_array_index (chain->streams, GstOggPad *, i);

    stream->start_time = -1;
    stream->map.accumulated_granule = 0;
  }
  ogg->building_chain = chain;
  GST_DEBUG_OBJECT (ogg, "Resetting current chain");
  ogg->current_chain = NULL;
  ogg->resync = TRUE;

  ogg->chunk_size = CHUNKSIZE;
}
