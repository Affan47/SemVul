gst_rtp_mpa_robust_depay_process (GstRTPBaseDepayload * depayload,
    GstBuffer * buf)
{
  GstRtpMPARobustDepay *rtpmpadepay;
  gint payload_len, offset;
  guint8 *payload;
  gboolean cont, dtype;
  guint av, size;
  GstClockTime timestamp;
  GstRTPBuffer rtp = { NULL };

  rtpmpadepay = GST_RTP_MPA_ROBUST_DEPAY (depayload);

  timestamp = GST_BUFFER_TIMESTAMP (buf);

  gst_rtp_buffer_map (buf, GST_MAP_READ, &rtp);

  payload_len = gst_rtp_buffer_get_payload_len (&rtp);
  if (payload_len <= 1)
    goto short_read;

  payload = gst_rtp_buffer_get_payload (&rtp);
  offset = 0;
  GST_LOG_OBJECT (rtpmpadepay, "payload_len: %d", payload_len);


  while (payload_len) {
    if (G_LIKELY (rtpmpadepay->has_descriptor)) {
      cont = ! !(payload[offset] & 0x80);
      dtype = ! !(payload[offset] & 0x40);
      if (dtype) {
        size = (payload[offset] & 0x3f) << 8 | payload[offset + 1];
        payload_len--;
        offset++;
      } else if (payload_len >= 2) {
        size = (payload[offset] & 0x3f);
        payload_len -= 2;
        offset += 2;
      } else {
        goto short_read;
      }
    } else {
      cont = FALSE;
      dtype = -1;
      size = payload_len;
    }

    GST_LOG_OBJECT (rtpmpadepay, "offset %d has cont: %d, dtype: %d, size: %d",
        offset, cont, dtype, size);

    buf = gst_rtp_buffer_get_payload_subbuffer (&rtp, offset,
        MIN (size, payload_len));

    if (cont) {
      av = gst_adapter_available (rtpmpadepay->adapter);
      if (G_UNLIKELY (!av)) {
        GST_DEBUG_OBJECT (rtpmpadepay,
            "discarding continuation fragment without prior fragment");
        gst_buffer_unref (buf);
      } else {
        av += gst_buffer_get_size (buf);
        gst_adapter_push (rtpmpadepay->adapter, buf);
        if (av == size) {
          timestamp = gst_adapter_prev_pts (rtpmpadepay->adapter, NULL);
          buf = gst_adapter_take_buffer (rtpmpadepay->adapter, size);
          GST_BUFFER_TIMESTAMP (buf) = timestamp;
          gst_rtp_mpa_robust_depay_submit_adu (rtpmpadepay, buf);
        } else if (av > size) {
          GST_DEBUG_OBJECT (rtpmpadepay,
              "assembled ADU size %d larger than expected %d; discarding",
              av, size);
          gst_adapter_clear (rtpmpadepay->adapter);
        }
      }
      size = payload_len;
    } else {

      if (payload_len == size) {

        GST_BUFFER_TIMESTAMP (buf) = timestamp;
        gst_rtp_mpa_robust_depay_submit_adu (rtpmpadepay, buf);
      } else if (payload_len < size) {

        gst_adapter_push (rtpmpadepay->adapter, buf);
        size = payload_len;
      }
    }

    offset += size;
    payload_len -= size;


    timestamp = GST_CLOCK_TIME_NONE;
  }
  gst_rtp_buffer_unmap (&rtp);

  return NULL;


short_read:
  {
    GST_ELEMENT_WARNING (rtpmpadepay, STREAM, DECODE,
        (NULL), ("Packet contains invalid data"));
    gst_rtp_buffer_unmap (&rtp);
    return NULL;
  }
}
