psmux_stream_pes_header_length (PsMuxStream * stream)
{
  guint8 packet_len;


  packet_len = 6;

  if (stream->pi.flags & PSMUX_PACKET_FLAG_PES_FULL_HEADER) {


    packet_len += 3;
    if (stream->pi.flags & PSMUX_PACKET_FLAG_PES_WRITE_PTS_DTS) {
      packet_len += 10;
    } else if (stream->pi.flags & PSMUX_PACKET_FLAG_PES_WRITE_PTS) {
      packet_len += 5;
    }
    if (stream->pi.flags & PSMUX_PACKET_FLAG_PES_EXT_STREAMID) {


      packet_len += 3;
    }
  }

  return packet_len;
}
