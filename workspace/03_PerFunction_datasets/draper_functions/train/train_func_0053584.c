clutter_gst_rgb24_upload (ClutterGstVideoSink * sink, GstBuffer * buffer)
{
  ClutterGstVideoSinkPrivate *priv = sink->priv;
  CoglPixelFormat format;
  CoglHandle tex;
  GstVideoFrame frame;

  if (priv->bgr)
    format = COGL_PIXEL_FORMAT_BGR_888;
  else
    format = COGL_PIXEL_FORMAT_RGB_888;

  if (!gst_video_frame_map (&frame, &priv->info, buffer, GST_MAP_READ))
    goto map_fail;

  tex = cogl_texture_new_from_data (priv->info.width,
      priv->info.height,
      CLUTTER_GST_TEXTURE_FLAGS,
      format, format, priv->info.stride[0], frame.data[0]);

  gst_video_frame_unmap (&frame);

  _create_paint_material (sink, tex, COGL_INVALID_HANDLE, COGL_INVALID_HANDLE);

  return TRUE;


map_fail:
  {
    GST_ERROR_OBJECT (sink, "Could not map incoming video frame");
    return FALSE;
  }
}
