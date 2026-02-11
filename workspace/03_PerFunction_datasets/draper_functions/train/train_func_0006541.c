parse_npt_time (const gchar * str, GstRTSPTime * time)
{
  if (strncmp (str, "now", 3) == 0) {
    time->type = GST_RTSP_TIME_NOW;
  } else if (str[0] == '\0') {
    time->type = GST_RTSP_TIME_END;
  } else if (strstr (str, ":")) {
    gfloat seconds;
    gint hours, mins;

    sscanf (str, "%2d:%2d:%f", &hours, &mins, &seconds);

    time->type = GST_RTSP_TIME_SECONDS;
    time->seconds = ((hours * 60) + mins) * 60 + seconds;
  } else {
    gfloat seconds;

    sscanf (str, "%f", &seconds);

    time->type = GST_RTSP_TIME_SECONDS;
    time->seconds = seconds;
  }
  return GST_RTSP_OK;
}
