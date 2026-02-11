gst_rtp_mp2t_pay_handle_buffer (GstRTPBasePayload * basepayload,
    GstBuffer * buffer)
{
  GstRTPMP2TPay *rtpmp2tpay;
  guint size, avail, packet_len;
  GstClockTime timestamp, duration;
  GstFlowReturn ret;

  rtpmp2tpay = GST_RTP_MP2T_PAY (basepayload);

  size = gst_buffer_get_size (buffer);
  timestamp = GST_BUFFER_TIMESTAMP (buffer);
  duration = GST_BUFFER_DURATION (buffer);

again:
  ret = GST_FLOW_OK;
  avail = gst_adapter_available (rtpmp2tpay->adapter);


  if (avail == 0) {
    rtpmp2tpay->first_ts = timestamp;
    rtpmp2tpay->duration = duration;
  }


  packet_len = gst_rtp_buffer_calc_packet_len (avail + size, 0, 0);


  if (!size || gst_rtp_base_payload_is_filled (basepayload,
          packet_len, rtpmp2tpay->duration + duration)) {
    ret = gst_rtp_mp2t_pay_flush (rtpmp2tpay);
    rtpmp2tpay->first_ts = timestamp;
    rtpmp2tpay->duration = duration;


  } else {
    if (GST_CLOCK_TIME_IS_VALID (duration))
      rtpmp2tpay->duration += duration;
  }


  if (buffer) {
    gst_adapter_push (rtpmp2tpay->adapter, buffer);
    buffer = NULL;
  }

  if (size >= (188 * 2)) {
    size = 0;
    goto again;
  }

  return ret;

}
