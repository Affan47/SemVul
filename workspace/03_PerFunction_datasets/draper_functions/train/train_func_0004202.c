npt_time_string (const GstRTSPTime * time, GString * string)
{
  gboolean res = TRUE;;

  switch (time->type) {
    case GST_RTSP_TIME_SECONDS:
      g_string_append_printf (string, "%f", time->seconds);
      break;
    case GST_RTSP_TIME_NOW:
      g_string_append (string, "now");
      break;
    case GST_RTSP_TIME_END:
      break;
    default:
      res = FALSE;
      break;
  }
  return res;
}
