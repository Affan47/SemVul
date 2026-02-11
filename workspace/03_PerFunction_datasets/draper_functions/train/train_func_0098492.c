gst_rtp_sbc_depay_process (GstRTPBaseDepayload * base, GstBuffer * in)
{
  GstRtpSbcDepay *depay = GST_RTP_SBC_DEPAY (base);
  GstBuffer *data = NULL;
  GstRTPBuffer rtp = { NULL };

  gboolean fragment, start, last;
  guint8 nframes;
  guint8 *payload;
  guint payload_len;

  gst_rtp_buffer_map (in, GST_MAP_READ, &rtp);

  GST_LOG_OBJECT (depay, "Got %" G_GSIZE_FORMAT " bytes",
      gst_buffer_get_size (in));

  if (gst_rtp_buffer_get_marker (&rtp)) {

    GST_WARNING_OBJECT (depay, "Marker bit was set");
    goto bad_packet;
  }

  payload = gst_rtp_buffer_get_payload (&rtp);
  payload_len = gst_rtp_buffer_get_payload_len (&rtp);

  fragment = payload[0] & 0x80;
  start = payload[0] & 0x40;
  last = payload[0] & 0x20;
  nframes = payload[0] & 0x0f;

  payload += 1;
  payload_len -= 1;

  data = gst_rtp_buffer_get_payload_subbuffer (&rtp, 1, -1);

  if (fragment) {

    GST_LOG_OBJECT (depay, "Got fragment");

    if (start && gst_adapter_available (depay->adapter)) {
      GST_WARNING_OBJECT (depay, "Missing last fragment");
      gst_adapter_clear (depay->adapter);

    } else if (!start && !gst_adapter_available (depay->adapter)) {
      GST_WARNING_OBJECT (depay, "Missing start fragment");
      gst_buffer_unref (data);
      data = NULL;
      goto out;
    }

    gst_adapter_push (depay->adapter, data);

    if (last) {
      data = gst_adapter_take_buffer (depay->adapter,
          gst_adapter_available (depay->adapter));
    } else
      data = NULL;

  } else {

    gint framelen, samples;

    GST_LOG_OBJECT (depay, "Got %d frames", nframes);

    if (gst_rtp_sbc_depay_get_params (depay, payload,
            payload_len, &framelen, &samples) < 0) {
      gst_adapter_clear (depay->adapter);
      goto bad_packet;
    }

    GST_LOG_OBJECT (depay, "Got payload of %d", payload_len);

    if (nframes * framelen > (gint) payload_len) {
      GST_WARNING_OBJECT (depay, "Short packet");
      goto bad_packet;
    } else if (nframes * framelen < (gint) payload_len) {
      GST_WARNING_OBJECT (depay, "Junk at end of packet");
    }
  }

out:
  gst_rtp_buffer_unmap (&rtp);
  return data;

bad_packet:
  GST_ELEMENT_WARNING (depay, STREAM, DECODE,
      ("Received invalid RTP payload, dropping"), (NULL));
  goto out;
}
