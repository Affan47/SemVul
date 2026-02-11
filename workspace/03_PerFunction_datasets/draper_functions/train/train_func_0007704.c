mpegts_packetizer_clear (MpegTSPacketizer2 * packetizer)
{
  if (packetizer->packet_size)
    packetizer->packet_size = 0;

  if (packetizer->streams) {
    int i;
    for (i = 0; i < 8192; i++) {
      if (packetizer->streams[i]) {
        mpegts_packetizer_stream_free (packetizer->streams[i]);
      }
    }
    memset (packetizer->streams, 0, 8192 * sizeof (MpegTSPacketizerStream *));
  }

  gst_adapter_clear (packetizer->adapter);
  packetizer->offset = 0;
  packetizer->empty = TRUE;
  packetizer->priv->need_sync = FALSE;
  packetizer->priv->map_data = NULL;
  packetizer->priv->map_size = 0;
  packetizer->priv->map_offset = 0;
  packetizer->priv->last_in_time = GST_CLOCK_TIME_NONE;
}
