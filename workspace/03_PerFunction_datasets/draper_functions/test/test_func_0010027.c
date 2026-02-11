gst_base_text_overlay_set_composition (GstBaseTextOverlay * overlay)
{
  gint xpos, ypos;
  GstVideoOverlayRectangle *rectangle;

  gst_base_text_overlay_get_pos (overlay, &xpos, &ypos);

  if (overlay->text_image) {
    gst_buffer_add_video_meta (overlay->text_image, GST_VIDEO_FRAME_FLAG_NONE,
        GST_VIDEO_OVERLAY_COMPOSITION_FORMAT_RGB,
        overlay->image_width, overlay->image_height);
    rectangle = gst_video_overlay_rectangle_new_raw (overlay->text_image,
        xpos, ypos, overlay->image_width, overlay->image_height,
        GST_VIDEO_OVERLAY_FORMAT_FLAG_PREMULTIPLIED_ALPHA);

    if (overlay->composition)
      gst_video_overlay_composition_unref (overlay->composition);
    overlay->composition = gst_video_overlay_composition_new (rectangle);
    gst_video_overlay_rectangle_unref (rectangle);

  } else if (overlay->composition) {
    gst_video_overlay_composition_unref (overlay->composition);
    overlay->composition = NULL;
  }
}
