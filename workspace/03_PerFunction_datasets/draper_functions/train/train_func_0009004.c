gst_rtp_mp4a_pay_handle_buffer (GstBaseRTPPayload * basepayload,
    GstBuffer * buffer)
{
  GstRtpMP4APay *rtpmp4apay;
  GstFlowReturn ret;
  GstBuffer *outbuf;
  guint count, mtu, size;
  guint8 *data;
  gboolean fragmented;
  GstClockTime timestamp;

  ret = GST_FLOW_OK;

  rtpmp4apay = GST_RTP_MP4A_PAY (basepayload);

  size = GST_BUFFER_SIZE (buffer);
  data = GST_BUFFER_DATA (buffer);
  timestamp = GST_BUFFER_TIMESTAMP (buffer);

  fragmented = FALSE;
  mtu = GST_BASE_RTP_PAYLOAD_MTU (rtpmp4apay);

  while (size > 0) {
    guint towrite;
    guint8 *payload;
    guint payload_len;
    guint packet_len;


    packet_len = gst_rtp_buffer_calc_packet_len (size, 0, 0);

    if (!fragmented) {

      count = size;
      while (count >= 0xff) {
        packet_len++;
        count -= 0xff;
      }
      packet_len++;
    }


    towrite = MIN (packet_len, mtu);


    payload_len = gst_rtp_buffer_calc_payload_len (towrite, 0, 0);

    GST_DEBUG_OBJECT (rtpmp4apay,
        "avail %d, towrite %d, packet_len %d, payload_len %d", size, towrite,
        packet_len, payload_len);


    outbuf = gst_rtp_buffer_new_allocate (payload_len, 0, 0);


    payload = gst_rtp_buffer_get_payload (outbuf);

    if (!fragmented) {

      count = size;
      while (count >= 0xff) {
        *payload++ = 0xff;
        payload_len--;
        count -= 0xff;
      }
      *payload++ = count;
      payload_len--;
    }


    memcpy (payload, data, payload_len);
    data += payload_len;
    size -= payload_len;


    gst_rtp_buffer_set_marker (outbuf, size == 0);


    GST_BUFFER_TIMESTAMP (outbuf) = timestamp;

    ret = gst_basertppayload_push (GST_BASE_RTP_PAYLOAD (rtpmp4apay), outbuf);

    fragmented = TRUE;
  }

  gst_buffer_unref (buffer);

  return ret;
}
