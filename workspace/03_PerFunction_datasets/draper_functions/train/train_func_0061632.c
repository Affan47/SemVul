test_enum_setting (GstUvcH264Src * self, guint offset, guint size,
    guint16 value)
{
  uvcx_video_config_probe_commit_t cur;
  uvcx_video_config_probe_commit_t req;
  guchar *req_p = (guchar *) & req;

  if (!xu_query (self, UVCX_VIDEO_CONFIG_PROBE, UVC_GET_CUR, (guchar *) & cur)) {
    GST_WARNING_OBJECT (self, " GET_CUR error");
    return FALSE;
  }

  req = cur;

  if (size == 1)
    *((guint8 *) (req_p + offset)) = (guint8) value;
  else
    *((guint16 *) (req_p + offset)) = value;

  if (!xu_query (self, UVCX_VIDEO_CONFIG_PROBE, UVC_SET_CUR, req_p)) {
    GST_WARNING_OBJECT (self, " SET_CUR error");
    return FALSE;
  }

  if (!xu_query (self, UVCX_VIDEO_CONFIG_PROBE, UVC_GET_CUR, req_p)) {
    GST_WARNING_OBJECT (self, " GET_CUR error");
    return FALSE;
  }

  if (!xu_query (self, UVCX_VIDEO_CONFIG_PROBE, UVC_SET_CUR, (guchar *) & cur)) {
    GST_WARNING_OBJECT (self, " SET_CUR error");
    return FALSE;
  }

  if (size == 1)
    return *((guint8 *) (req_p + offset)) == (guint8) value;
  else
    return *((guint16 *) (req_p + offset)) == value;
}
