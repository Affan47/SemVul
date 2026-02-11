gst_asteriskh263_chain (GstPad * pad, GstBuffer * buf)
{
  GstAsteriskh263 *asteriskh263;
  GstBuffer *outbuf;
  GstFlowReturn ret;

  asteriskh263 = GST_ASTERISK_H263 (GST_OBJECT_PARENT (pad));

  if (!gst_rtp_buffer_validate (buf))
    goto bad_packet;

  {
    gint payload_len;
    guint8 *payload;
    gboolean M;
    guint32 timestamp;
    guint32 samples;
    guint16 asterisk_len;

    payload_len = gst_rtp_buffer_get_payload_len (buf);
    payload = gst_rtp_buffer_get_payload (buf);

    M = gst_rtp_buffer_get_marker (buf);
    timestamp = gst_rtp_buffer_get_timestamp (buf);

    outbuf = gst_buffer_new_and_alloc (payload_len +
        GST_ASTERISKH263_HEADER_LEN);


    asterisk_len = payload_len;
    if (M)
      asterisk_len |= 0x8000;
    if (!asteriskh263->lastts)
      asteriskh263->lastts = timestamp;
    samples = timestamp - asteriskh263->lastts;
    asteriskh263->lastts = timestamp;

    GST_ASTERISKH263_HEADER_TIMESTAMP (outbuf) = g_htonl (samples);
    GST_ASTERISKH263_HEADER_LENGTH (outbuf) = g_htons (asterisk_len);


    memcpy (GST_BUFFER_DATA (outbuf) + GST_ASTERISKH263_HEADER_LEN, payload,
        payload_len);

    GST_BUFFER_TIMESTAMP (outbuf) = timestamp;
    gst_buffer_set_caps (outbuf,
        (GstCaps *) gst_pad_get_pad_template_caps (asteriskh263->srcpad));

    ret = gst_pad_push (asteriskh263->srcpad, outbuf);

    gst_buffer_unref (buf);
  }

  return ret;

bad_packet:
  {
    GST_DEBUG ("Packet does not validate");
    gst_buffer_unref (buf);
    return GST_FLOW_ERROR;
  }
}
