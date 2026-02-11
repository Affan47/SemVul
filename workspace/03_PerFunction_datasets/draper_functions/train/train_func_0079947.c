gst_rtp_ac3_depay_process (GstRTPBaseDepayload * depayload, GstBuffer * buf)
{
  GstRtpAC3Depay *rtpac3depay;
  GstBuffer *outbuf;
  GstRTPBuffer rtp = { NULL, };
  guint8 *payload;
  guint16 FT, NF;

  rtpac3depay = GST_RTP_AC3_DEPAY (depayload);

  gst_rtp_buffer_map (buf, GST_MAP_READ, &rtp);

  if (gst_rtp_buffer_get_payload_len (&rtp) < 2)
    goto empty_packet;

  payload = gst_rtp_buffer_get_payload (&rtp);


  FT = payload[0] & 0x3;
  NF = payload[1];

  GST_DEBUG_OBJECT (rtpac3depay, "FT: %d, NF: %d", FT, NF);


  outbuf = gst_rtp_buffer_get_payload_subbuffer (&rtp, 2, -1);

  gst_rtp_buffer_unmap (&rtp);

  if (outbuf)
    GST_DEBUG_OBJECT (rtpac3depay, "pushing buffer of size %" G_GSIZE_FORMAT,
        gst_buffer_get_size (outbuf));

  return outbuf;


empty_packet:
  {
    GST_ELEMENT_WARNING (rtpac3depay, STREAM, DECODE,
        ("Empty Payload."), (NULL));
    gst_rtp_buffer_unmap (&rtp);
    return NULL;
  }
}
