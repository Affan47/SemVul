gst_video_format_to_string (GstVideoFormat format)
{
  g_return_val_if_fail (format != GST_VIDEO_FORMAT_UNKNOWN, NULL);

  if (format >= G_N_ELEMENTS (formats))
    return NULL;

  return GST_VIDEO_FORMAT_INFO_NAME (&formats[format].info);
}
