gst_rtp_g723_depay_process (GstRTPBaseDepayload * depayload, GstBuffer * buf)
{
  GstRtpG723Depay *rtpg723depay;
  GstBuffer *outbuf = NULL;
  gint payload_len;
  gboolean marker;
  GstRTPBuffer rtp = { NULL };

  rtpg723depay = GST_RTP_G723_DEPAY (depayload);

  gst_rtp_buffer_map (buf, GST_MAP_READ, &rtp);

  payload_len = gst_rtp_buffer_get_payload_len (&rtp);


  if (payload_len < 4)
    goto too_small;

  GST_LOG_OBJECT (rtpg723depay, "payload len %d", payload_len);

  outbuf = gst_rtp_buffer_get_payload_buffer (&rtp);
  marker = gst_rtp_buffer_get_marker (&rtp);
  gst_rtp_buffer_unmap (&rtp);

  if (marker) {

    GST_BUFFER_FLAG_SET (outbuf, GST_BUFFER_FLAG_RESYNC);
  }

  GST_LOG_OBJECT (depayload, "pushing buffer of size %" G_GSIZE_FORMAT,
      gst_buffer_get_size (outbuf));

  return outbuf;


too_small:
  {
    GST_ELEMENT_WARNING (rtpg723depay, STREAM, DECODE,
        (NULL), ("G723 RTP payload too small (%d)", payload_len));
    goto bad_packet;
  }
bad_packet:
  {

    gst_rtp_buffer_unmap (&rtp);
    return NULL;
  }
}
