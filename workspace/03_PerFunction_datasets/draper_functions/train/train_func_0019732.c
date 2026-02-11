find_pcr_packet (MpegTSBase * base, guint64 offset, gint64 length,
    TSPcrOffset * pcroffset)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstTSDemux *demux = GST_TS_DEMUX (base);
  MpegTSBaseProgram *program;
  GstBuffer *buf;
  gboolean done = FALSE;
  guint64 scan_offset = 0;

  GST_DEBUG ("Scanning for PCR between:%" G_GINT64_FORMAT
      " and the end:%" G_GINT64_FORMAT, offset, offset + length);


  program = demux->program;
  if (G_UNLIKELY (program == NULL))
    return GST_FLOW_ERROR;

  mpegts_packetizer_flush (base->packetizer);
  if (offset >= 4 && base->packetizer->packet_size == MPEGTS_M2TS_PACKETSIZE)
    offset -= 4;

  while (!done && scan_offset < length) {
    ret =
        gst_pad_pull_range (base->sinkpad, offset + scan_offset,
        50 * MPEGTS_MAX_PACKETSIZE, &buf);
    if (ret != GST_FLOW_OK)
      goto beach;
    mpegts_packetizer_push (base->packetizer, buf);
    done = process_pes (base, pcroffset);
    scan_offset += 50 * MPEGTS_MAX_PACKETSIZE;
  }

  if (!done || scan_offset >= length) {
    GST_WARNING ("No PCR found!");
    ret = GST_FLOW_ERROR;
    goto beach;
  }

beach:
  mpegts_packetizer_flush (base->packetizer);
  return ret;
}
