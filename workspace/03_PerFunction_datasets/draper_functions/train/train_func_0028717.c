gst_rtp_mpa_pay_handle_buffer (GstRTPBasePayload * basepayload,
    GstBuffer * buffer)
{
  GstRtpMPAPay *rtpmpapay;
  GstFlowReturn ret;
  guint size, avail;
  guint packet_len;
  GstClockTime duration, timestamp;

  rtpmpapay = GST_RTP_MPA_PAY (basepayload);

  size = gst_buffer_get_size (buffer);
  duration = GST_BUFFER_DURATION (buffer);
  timestamp = GST_BUFFER_TIMESTAMP (buffer);

  if (GST_BUFFER_IS_DISCONT (buffer)) {
    GST_DEBUG_OBJECT (rtpmpapay, "DISCONT");
    gst_rtp_mpa_pay_reset (rtpmpapay);
  }

  avail = gst_adapter_available (rtpmpapay->adapter);


  packet_len = gst_rtp_buffer_calc_packet_len (4 + avail + size, 0, 0);


  if (gst_rtp_base_payload_is_filled (basepayload,
          packet_len, rtpmpapay->duration + duration)) {
    ret = gst_rtp_mpa_pay_flush (rtpmpapay);
    avail = 0;
  } else {
    ret = GST_FLOW_OK;
  }

  if (avail == 0) {
    GST_DEBUG_OBJECT (rtpmpapay,
        "first packet, save timestamp %" GST_TIME_FORMAT,
        GST_TIME_ARGS (timestamp));
    rtpmpapay->first_ts = timestamp;
    rtpmpapay->duration = 0;
  }

  gst_adapter_push (rtpmpapay->adapter, buffer);
  rtpmpapay->duration = duration;

  return ret;
}
