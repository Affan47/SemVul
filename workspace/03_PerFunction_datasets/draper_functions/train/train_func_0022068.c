mpegts_try_discover_packet_size (MpegTSPacketizer2 * packetizer)
{
  MpegTSPacketizerPrivate *priv = packetizer->priv;
  guint8 *data;
  gsize size, i, j;

  static const guint psizes[] = {
    MPEGTS_NORMAL_PACKETSIZE,
    MPEGTS_M2TS_PACKETSIZE,
    MPEGTS_DVB_ASI_PACKETSIZE,
    MPEGTS_ATSC_PACKETSIZE
  };

  if (!mpegts_packetizer_map (packetizer, 4 * MPEGTS_MAX_PACKETSIZE))
    return FALSE;

  size = priv->map_size - priv->map_offset;
  data = priv->map_data + priv->map_offset;

  for (i = 0; i + 3 * MPEGTS_MAX_PACKETSIZE < size; i++) {

    if (data[i] != PACKET_SYNC_BYTE)
      continue;


    for (j = 0; j < G_N_ELEMENTS (psizes); j++) {
      guint packet_size = psizes[j];

      if (data[i + packet_size] == PACKET_SYNC_BYTE &&
          data[i + 2 * packet_size] == PACKET_SYNC_BYTE &&
          data[i + 3 * packet_size] == PACKET_SYNC_BYTE) {
        packetizer->packet_size = packet_size;
        goto out;
      }
    }
  }

out:
  priv->map_offset += i;

  if (packetizer->packet_size == 0) {
    GST_DEBUG ("Could not determine packet size in %" G_GSIZE_FORMAT
        " bytes buffer, flush %" G_GSIZE_FORMAT " bytes", size, i);
    mpegts_packetizer_flush_bytes (packetizer, priv->map_offset);
    return FALSE;
  }

  GST_INFO ("have packetsize detected: %u bytes", packetizer->packet_size);

  if (packetizer->packet_size == MPEGTS_M2TS_PACKETSIZE &&
      priv->map_offset >= 4)
    priv->map_offset -= 4;

  return TRUE;
}
