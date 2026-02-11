mpegts_packetizer_dispose (GObject * object)
{
  MpegTSPacketizer2 *packetizer = GST_MPEGTS_PACKETIZER (object);

  if (!packetizer->disposed) {
    if (packetizer->packet_size)
      packetizer->packet_size = 0;
    if (packetizer->streams) {
      int i;
      for (i = 0; i < 8192; i++) {
        if (packetizer->streams[i])
          mpegts_packetizer_stream_free (packetizer->streams[i]);
      }
      g_free (packetizer->streams);
    }

    gst_adapter_clear (packetizer->adapter);
    g_object_unref (packetizer->adapter);
    packetizer->disposed = TRUE;
    packetizer->offset = 0;
    packetizer->empty = TRUE;

    flush_observations (packetizer);
  }

  if (G_OBJECT_CLASS (mpegts_packetizer_parent_class)->dispose)
    G_OBJECT_CLASS (mpegts_packetizer_parent_class)->dispose (object);
}
