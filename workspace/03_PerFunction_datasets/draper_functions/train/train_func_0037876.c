gst_rtp_quicktime_parse_sd (GstRtpXQTDepay * rtpxqtdepay, guint8 * data,
    guint data_len)
{
  gint len;
  guint32 fourcc;

  if (data_len < 8)
    goto too_short;

  len = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
  if (len > data_len)
    goto too_short;

  fourcc = QT_FOURCC (data + 4);

  GST_DEBUG_OBJECT (rtpxqtdepay, "parsing %" GST_FOURCC_FORMAT,
      GST_FOURCC_ARGS (fourcc));

  switch (fourcc) {
    case FOURCC_avc1:
    case FOURCC_avc3:
    {
      guint32 chlen;

      if (len < 0x56)
        goto too_short;
      len -= 0x56;
      data += 0x56;


      while (len >= 8) {
        chlen = QT_UINT32 (data);
        fourcc = QT_FOURCC (data + 4);
        if (fourcc == FOURCC_avcC) {
          GstBuffer *buf;
          gint size;
          GstCaps *caps;

          GST_DEBUG_OBJECT (rtpxqtdepay, "found avcC codec_data in sd, %u",
              chlen);


          if (chlen < len)
            size = chlen - 8;
          else
            size = len - 8;

          buf = gst_buffer_new_and_alloc (size);
          gst_buffer_fill (buf, 0, data + 8, size);
          caps = gst_caps_new_simple ("video/x-h264",
              "codec_data", GST_TYPE_BUFFER, buf, NULL);
          gst_buffer_unref (buf);
          gst_pad_set_caps (GST_RTP_BASE_DEPAYLOAD (rtpxqtdepay)->srcpad, caps);
          gst_caps_unref (caps);
          break;
        }
        len -= chlen;
        data += chlen;
      }
      break;
    }
    default:
      break;
  }
  return TRUE;


too_short:
  {
    return FALSE;
  }
}
