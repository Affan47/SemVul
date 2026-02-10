gst_rtp_h263p_pay_flush (GstRtpH263PPay * rtph263ppay)
{
  guint avail;
  GstBuffer *outbuf;
  GstFlowReturn ret;
  gboolean fragmented;

  avail = gst_adapter_available (rtph263ppay->adapter);
  if (avail == 0)
    return GST_FLOW_OK;

  fragmented = FALSE;


  while (avail > 0) {
    guint towrite;
    guint8 *payload;
    guint payload_len;
    gint header_len;
    guint next_gop = 0;
    gboolean found_gob = FALSE;
    GstRTPBuffer rtp = { NULL };

    if (rtph263ppay->fragmentation_mode == GST_FRAGMENTATION_MODE_SYNC) {

      guint parsed_len = 3;
      const guint8 *parse_data = NULL;

      parse_data = gst_adapter_map (rtph263ppay->adapter, avail);


      if (avail >= 3 && *parse_data == 0 && *(parse_data + 1) == 0
          && *(parse_data + 2) >= 0x80) {
        GST_DEBUG_OBJECT (rtph263ppay, " Found GOB header");
        found_gob = TRUE;
      }


      while (parsed_len + 2 < avail) {
        if (parse_data[parsed_len] == 0 && parse_data[parsed_len + 1] == 0
            && parse_data[parsed_len + 2] >= 0x80) {
          next_gop = parsed_len;
          GST_DEBUG_OBJECT (rtph263ppay, " Next GOB Detected at :  %d",
              next_gop);
          break;
        }
        parsed_len++;
      }
      gst_adapter_unmap (rtph263ppay->adapter);
    }


    header_len = (fragmented && !found_gob) ? 2 : 0;

    towrite = MIN (avail, gst_rtp_buffer_calc_payload_len
        (GST_RTP_BASE_PAYLOAD_MTU (rtph263ppay) - header_len, 0, 0));

    if (next_gop > 0)
      towrite = MIN (next_gop, towrite);

    payload_len = header_len + towrite;

    outbuf = gst_rtp_buffer_new_allocate (payload_len, 0, 0);

    gst_rtp_buffer_map (outbuf, GST_MAP_WRITE, &rtp);

    gst_rtp_buffer_set_marker (&rtp, avail > towrite ? 0 : 1);

    payload = gst_rtp_buffer_get_payload (&rtp);

    gst_adapter_copy (rtph263ppay->adapter, &payload[header_len], 0, towrite);


    payload[0] = (fragmented && !found_gob) ? 0x00 : 0x04;
    payload[1] = 0;

    GST_BUFFER_TIMESTAMP (outbuf) = rtph263ppay->first_timestamp;
    GST_BUFFER_DURATION (outbuf) = rtph263ppay->first_duration;
    gst_rtp_buffer_unmap (&rtp);

    gst_adapter_flush (rtph263ppay->adapter, towrite);

    ret =
        gst_rtp_base_payload_push (GST_RTP_BASE_PAYLOAD (rtph263ppay), outbuf);

    avail -= towrite;
    fragmented = TRUE;
  }

  return ret;
}
