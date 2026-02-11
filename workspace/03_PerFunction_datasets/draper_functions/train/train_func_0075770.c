mpegts_packetizer_parse_adaptation_field_control (MpegTSPacketizer2 *
    packetizer, MpegTSPacketizerPacket * packet)
{
  guint8 length, afcflags;
  guint8 *data;

  length = *packet->data++;


  if (!length) {
    packet->afc_flags = 0;
    return TRUE;
  }

  if (packet->adaptation_field_control == 0x02) {

    if (length != 183) {
      GST_DEBUG ("PID %d afc == 0x%x and length %d != 183",
          packet->pid, packet->adaptation_field_control, length);
    }
  } else if (length > 182) {
    GST_DEBUG ("PID %d afc == 0x%01x and length %d > 182",
        packet->pid, packet->adaptation_field_control, length);
  }

  if (packet->data + length > packet->data_end) {
    GST_DEBUG ("PID %d afc length %d overflows the buffer current %d max %d",
        packet->pid, length, (gint) (packet->data - packet->data_start),
        (gint) (packet->data_end - packet->data_start));
    return FALSE;
  }

  data = packet->data;
  packet->data += length;

  afcflags = packet->afc_flags = *data++;


  if (afcflags & MPEGTS_AFC_PCR_FLAG) {
    packet->pcr = mpegts_packetizer_compute_pcr (data);
    *data += 6;
  }


  if (afcflags & MPEGTS_AFC_OPCR_FLAG) {
    packet->opcr = mpegts_packetizer_compute_pcr (data);
    *data += 6;
  }

  return TRUE;
}
