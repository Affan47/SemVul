gst_rtp_gst_pay_create_from_adapter (GstRtpGSTPay * rtpgstpay,
    GstClockTime timestamp)
{
  guint avail;
  guint frag_offset;
  GstBufferList *list;

  avail = gst_adapter_available (rtpgstpay->adapter);
  if (avail == 0)
    return FALSE;

  list = gst_buffer_list_new ();
  frag_offset = 0;

  while (avail) {
    guint towrite;
    guint8 *payload;
    guint payload_len;
    guint packet_len;
    GstBuffer *outbuf;
    GstRTPBuffer rtp = { NULL };
    GstBuffer *paybuf;


    packet_len = gst_rtp_buffer_calc_packet_len (8 + avail, 0, 0);


    towrite = MIN (packet_len, GST_RTP_BASE_PAYLOAD_MTU (rtpgstpay));


    payload_len = gst_rtp_buffer_calc_payload_len (towrite, 0, 0);


    outbuf = gst_rtp_buffer_new_allocate (8, 0, 0);

    gst_rtp_buffer_map (outbuf, GST_MAP_WRITE, &rtp);
    payload = gst_rtp_buffer_get_payload (&rtp);

    GST_DEBUG_OBJECT (rtpgstpay, "new packet len %u, frag %u", packet_len,
        frag_offset);


    payload[0] = rtpgstpay->flags;
    payload[1] = rtpgstpay->etype;
    payload[2] = payload[3] = 0;
    payload[4] = frag_offset >> 24;
    payload[5] = frag_offset >> 16;
    payload[6] = frag_offset >> 8;
    payload[7] = frag_offset & 0xff;

    payload += 8;
    payload_len -= 8;

    frag_offset += payload_len;
    avail -= payload_len;

    if (avail == 0)
      gst_rtp_buffer_set_marker (&rtp, TRUE);

    gst_rtp_buffer_unmap (&rtp);


    GST_DEBUG_OBJECT (rtpgstpay, "take %u bytes from adapter", payload_len);
    paybuf = gst_adapter_take_buffer_fast (rtpgstpay->adapter, payload_len);


    gst_buffer_append (outbuf, paybuf);

    GST_BUFFER_TIMESTAMP (outbuf) = timestamp;


    gst_buffer_list_insert (list, -1, outbuf);
  }

  rtpgstpay->flags &= 0x70;
  rtpgstpay->etype = 0;
  rtpgstpay->pending_buffers = g_list_append (rtpgstpay->pending_buffers, list);

  return TRUE;
}
