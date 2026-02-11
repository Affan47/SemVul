gst_rtp_vorbis_pay_payload_buffer (GstRtpVorbisPay * rtpvorbispay, guint8 VDT,
    guint8 * data, guint size, GstClockTime timestamp, GstClockTime duration,
    guint not_in_length)
{
  GstFlowReturn ret = GST_FLOW_OK;
  guint newsize;
  guint packet_len;
  GstClockTime newduration;
  gboolean flush;
  guint plen;
  guint8 *ppos, *payload;
  gboolean fragmented;
  GstRTPBuffer rtp = { NULL };


  newduration = rtpvorbispay->payload_duration;
  if (duration != GST_CLOCK_TIME_NONE)
    newduration += duration;

  newsize = rtpvorbispay->payload_pos + 2 + size;
  packet_len = gst_rtp_buffer_calc_packet_len (newsize, 0, 0);


  flush = gst_rtp_base_payload_is_filled (GST_RTP_BASE_PAYLOAD (rtpvorbispay),
      packet_len, newduration);

  flush |= (rtpvorbispay->payload_pkts == 15);

  if (rtpvorbispay->packet)
    flush |= (rtpvorbispay->payload_VDT != VDT);
  if (flush)
    ret = gst_rtp_vorbis_pay_flush_packet (rtpvorbispay);


  if (!rtpvorbispay->packet) {
    gst_rtp_vorbis_pay_init_packet (rtpvorbispay, VDT, timestamp);
  }

  gst_rtp_buffer_map (rtpvorbispay->packet, GST_MAP_WRITE, &rtp);
  payload = gst_rtp_buffer_get_payload (&rtp);
  ppos = payload + rtpvorbispay->payload_pos;
  fragmented = FALSE;


  do {
    plen = MIN (rtpvorbispay->payload_left - 2, size);

    GST_LOG_OBJECT (rtpvorbispay, "append %u bytes", plen);


    ppos[0] = ((plen - not_in_length) >> 8) & 0xff;
    ppos[1] = ((plen - not_in_length) & 0xff);
    if (plen)
      memcpy (&ppos[2], data, plen);


    not_in_length = 0;

    size -= plen;
    data += plen;

    rtpvorbispay->payload_pos += plen + 2;
    rtpvorbispay->payload_left -= plen + 2;

    if (fragmented) {
      if (size == 0)

        rtpvorbispay->payload_F = 0x3;
      else

        rtpvorbispay->payload_F = 0x2;
    } else {
      if (size > 0) {


        rtpvorbispay->payload_F = 0x1;
        fragmented = TRUE;
      }
    }
    if (fragmented) {
      gst_rtp_buffer_unmap (&rtp);

      rtpvorbispay->payload_pkts = 0;
      ret = gst_rtp_vorbis_pay_flush_packet (rtpvorbispay);

      if (size > 0) {

        gst_rtp_vorbis_pay_init_packet (rtpvorbispay,
            rtpvorbispay->payload_VDT, timestamp);
        gst_rtp_buffer_map (rtpvorbispay->packet, GST_MAP_WRITE, &rtp);
        payload = gst_rtp_buffer_get_payload (&rtp);
        ppos = payload + rtpvorbispay->payload_pos;
      }
    } else {


      rtpvorbispay->payload_pkts++;
      if (duration != GST_CLOCK_TIME_NONE)
        rtpvorbispay->payload_duration += duration;
    }
  } while (size);

  if (rtp.buffer)
    gst_rtp_buffer_unmap (&rtp);

  return ret;
}
