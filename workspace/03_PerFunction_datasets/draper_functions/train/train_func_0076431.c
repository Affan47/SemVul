gst_video_overlay_composition_new (GstVideoOverlayRectangle * rectangle)
{
  GstVideoOverlayComposition *comp;


  g_return_val_if_fail (GST_IS_VIDEO_OVERLAY_RECTANGLE (rectangle), NULL);

  comp = (GstVideoOverlayComposition *)
      gst_mini_object_new (GST_TYPE_VIDEO_OVERLAY_COMPOSITION);

  comp->rectangles = g_new0 (GstVideoOverlayRectangle *, RECTANGLE_ARRAY_STEP);
  comp->rectangles[0] = gst_video_overlay_rectangle_ref (rectangle);
  comp->num_rectangles = 1;

  comp->seq_num = gst_video_overlay_get_seqnum ();


  comp->min_seq_num_used = rectangle->seq_num;

  GST_LOG ("new composition %p: seq_num %u with rectangle %p", comp,
      comp->seq_num, rectangle);

  return comp;
}
