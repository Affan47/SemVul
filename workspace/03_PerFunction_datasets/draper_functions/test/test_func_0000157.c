gst_video_overlay_composition_copy (GstVideoOverlayComposition * comp)
{
  GstVideoOverlayComposition *copy;
  GstVideoOverlayRectangle *rect;
  guint n;

  g_return_val_if_fail (GST_IS_VIDEO_OVERLAY_COMPOSITION (comp), NULL);

  if (G_LIKELY (comp->num_rectangles == 0))
    return gst_video_overlay_composition_new (NULL);

  rect = gst_video_overlay_rectangle_copy (comp->rectangles[0]);
  copy = gst_video_overlay_composition_new (rect);
  gst_video_overlay_rectangle_unref (rect);

  for (n = 1; n < comp->num_rectangles; ++n) {
    rect = gst_video_overlay_rectangle_copy (comp->rectangles[n]);
    gst_video_overlay_composition_add_rectangle (copy, rect);
    gst_video_overlay_rectangle_unref (rect);
  }

  return copy;
}
