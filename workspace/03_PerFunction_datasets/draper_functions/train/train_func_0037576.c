gst_rtp_theora_pay_payload_buffer (GstRtpTheoraPay * rtptheorapay, guint8 TDT,
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


  newduration = rtptheorapay->payload_duration;
  if (duration != GST_CLOCK_TIME_NONE)
    newduration += duration;

  newsize = rtptheorapay->payload_pos + 2 + size;
  packet_len = gst_rtp_buffer_calc_packet_len (newsize, 0, 0);


  flush = gst_basertppayload_is_filled (GST_BASE_RTP_PAYLOAD (rtptheorapay),
      packet_len, newduration);

  flush |= (rtptheorapay->payload_pkts == 15);

  if (rtptheorapay->packet)
    flush |= (rtptheorapay->payload_TDT != TDT);
  if (flush)
    ret = gst_rtp_theora_pay_flush_packet (rtptheorapay);


  if (!rtptheorapay->packet) {
    gst_rtp_theora_pay_init_packet (rtptheorapay, TDT, timestamp);
  }

  payload = gst_rtp_buffer_get_payload (rtptheorapay->packet);
  ppos = payload + rtptheorapay->payload_pos;
  fragmented = FALSE;


  do {
    plen = MIN (rtptheorapay->payload_left - 2, size);

    GST_DEBUG_OBJECT (rtptheorapay, "append %u bytes", plen);


    ppos[0] = ((plen - not_in_length) >> 8) & 0xff;
    ppos[1] = ((plen - not_in_length) & 0xff);
    if (plen)
      memcpy (&ppos[2], data, plen);


    not_in_length = 0;

    size -= plen;
    data += plen;

    rtptheorapay->payload_pos += plen + 2;
    rtptheorapay->payload_left -= plen + 2;

    if (fragmented) {
      if (size == 0)

        rtptheorapay->payload_F = 0x3;
      else

        rtptheorapay->payload_F = 0x2;
    } else {
      if (size > 0) {


        rtptheorapay->payload_F = 0x1;
        fragmented = TRUE;
      }
    }
    if (fragmented) {

      rtptheorapay->payload_pkts = 0;
      ret = gst_rtp_theora_pay_flush_packet (rtptheorapay);

      if (size > 0) {

        gst_rtp_theora_pay_init_packet (rtptheorapay,
            rtptheorapay->payload_TDT, timestamp);
        payload = gst_rtp_buffer_get_payload (rtptheorapay->packet);
        ppos = payload + rtptheorapay->payload_pos;
      }
    } else {


      rtptheorapay->payload_pkts++;
      if (duration != GST_CLOCK_TIME_NONE)
        rtptheorapay->payload_duration += duration;
    }
  } while (size);

  return ret;
}
