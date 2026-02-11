gst_video_overlay_rectangle_get_pixels_unscaled_argb (GstVideoOverlayRectangle *
    rectangle, guint * width, guint * height, guint * stride,
    GstVideoOverlayFormatFlags flags)
{
  g_return_val_if_fail (GST_IS_VIDEO_OVERLAY_RECTANGLE (rectangle), NULL);
  g_return_val_if_fail (width != NULL, NULL);
  g_return_val_if_fail (height != NULL, NULL);
  g_return_val_if_fail (stride != NULL, NULL);
  g_return_val_if_fail (flags == 0, NULL);

  *width = rectangle->width;
  *height = rectangle->height;
  *stride = rectangle->stride;

  return rectangle->pixels;
}
