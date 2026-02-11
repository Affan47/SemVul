gst_uvc_h264_src_get_boolean_setting (GstUvcH264Src * self, gchar * property,
    gboolean * changeable, gboolean * default_value)
{
  guint8 min, def, max;
  gboolean ret = FALSE;

  if (g_strcmp0 (property, "enable-sei") == 0) {
    ret = probe_setting (self, UVCX_VIDEO_CONFIG_PROBE,
        offsetof (uvcx_video_config_probe_commit_t, bTimestamp), 1,
        &min, &def, &max);
    *changeable = (min != max);
    *default_value = (def != 0);
  } else if (g_strcmp0 (property, "preview-flipped") == 0) {
    ret = probe_setting (self, UVCX_VIDEO_CONFIG_PROBE,
        offsetof (uvcx_video_config_probe_commit_t, bPreviewFlipped), 1,
        &min, &def, &max);
    *changeable = (min != max);
    *default_value = (def != 0);
  } else if (g_strcmp0 (property, "fixed-framerate") == 0) {
    ret = probe_setting (self, UVCX_VIDEO_CONFIG_PROBE,
        offsetof (uvcx_video_config_probe_commit_t, bRateControlMode), 1,
        &min, &def, &max);
    *changeable = ((max & UVC_H264_RATECONTROL_FIXED_FRM_FLG) != 0);
    *default_value = ((def & UVC_H264_RATECONTROL_FIXED_FRM_FLG) != 0);
  }

  return ret;
}
