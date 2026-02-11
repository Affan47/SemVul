setup_pcm_mapper (GstOggStream * pad, ogg_packet * packet)
{
  guint8 *data = packet->packet;
  int format;
  int channels;
  GstCaps *caps;

  pad->granulerate_n = GST_READ_UINT32_LE (data + 16);
  pad->granulerate_d = 1;
  GST_LOG ("sample rate: %d", pad->granulerate_n);

  format = GST_READ_UINT32_LE (data + 12);
  channels = GST_READ_UINT8 (data + 21);

  pad->n_header_packets = 2 + GST_READ_UINT32_LE (data + 24);

  if (pad->granulerate_n == 0)
    return FALSE;

  switch (format) {
    case OGGPCM_FMT_S8:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "S8", NULL);
      break;
    case OGGPCM_FMT_U8:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "U8", NULL);
      break;
    case OGGPCM_FMT_S16_LE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "S16LE", NULL);
      break;
    case OGGPCM_FMT_S16_BE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "S16BE", NULL);
      break;
    case OGGPCM_FMT_S24_LE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "S24LE", NULL);
      break;
    case OGGPCM_FMT_S24_BE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "S24BE", NULL);
      break;
    case OGGPCM_FMT_S32_LE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "S32LE", NULL);
      break;
    case OGGPCM_FMT_S32_BE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "S32BE", NULL);
      break;
    case OGGPCM_FMT_ULAW:
      caps = gst_caps_new_empty_simple ("audio/x-mulaw");
      break;
    case OGGPCM_FMT_ALAW:
      caps = gst_caps_new_empty_simple ("audio/x-alaw");
      break;
    case OGGPCM_FMT_FLT32_LE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "F32LE", NULL);
      break;
    case OGGPCM_FMT_FLT32_BE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "F32BE", NULL);
      break;
    case OGGPCM_FMT_FLT64_LE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "F64LE", NULL);
      break;
    case OGGPCM_FMT_FLT64_BE:
      caps = gst_caps_new_simple ("audio/x-raw",
          "format", G_TYPE_STRING, "F64BE", NULL);
      break;
    default:
      return FALSE;
  }

  gst_caps_set_simple (caps,
      "layout", G_TYPE_STRING, "interleaved",
      "rate", G_TYPE_INT, pad->granulerate_n,
      "channels", G_TYPE_INT, channels, NULL);
  pad->caps = caps;

  return TRUE;
}
