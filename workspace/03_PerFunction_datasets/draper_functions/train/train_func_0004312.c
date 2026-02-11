gst_codec_utils_h264_get_profile (const guint8 * sps, guint len)
{
  const gchar *profile = NULL;
  gint csf1, csf3;

  g_return_val_if_fail (sps != NULL, NULL);

  if (len < 2)
    return NULL;

  GST_MEMDUMP ("SPS", sps, len);

  csf1 = (sps[1] & 0x40) >> 6;
  csf3 = (sps[1] & 0x10) >> 4;

  switch (sps[0]) {
    case 66:
      if (csf1)
        profile = "constrained-baseline";
      else
        profile = "baseline";
      break;
    case 77:
      profile = "main";
      break;
    case 88:
      profile = "extended";
      break;
    case 100:
      profile = "high";
      break;
    case 110:
      if (csf3)
        profile = "high-10-intra";
      else
        profile = "high-10";
      break;
    case 122:
      if (csf3)
        profile = "high-4:2:2-intra";
      else
        profile = "high-4:2:2";
      break;
    case 244:
      if (csf3)
        profile = "high-4:4:4-intra";
      else
        profile = "high-4:4:4";
      break;
    case 44:
      profile = "cavlc-4:4:4-intra";
      break;
    case 118:
      profile = "multiview-high";
      break;
    case 128:
      profile = "stereo-high";
      break;
    default:
      return NULL;
  }

  return profile;
}
