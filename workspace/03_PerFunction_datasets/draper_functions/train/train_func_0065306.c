gst_streaktv_transform_frame (GstVideoFilter * vfilter,
    GstVideoFrame * in_frame, GstVideoFrame * out_frame)
{
  GstStreakTV *filter = GST_STREAKTV (vfilter);
  guint32 *src, *dest;
  gint i, cf;
  gint video_area, width, height;
  guint32 **planetable = filter->planetable;
  gint plane = filter->plane;
  guint stride_mask, stride_shift, stride;

  src = GST_VIDEO_FRAME_PLANE_DATA (in_frame, 0);
  dest = GST_VIDEO_FRAME_PLANE_DATA (out_frame, 0);

  width = GST_VIDEO_FRAME_WIDTH (in_frame);
  height = GST_VIDEO_FRAME_HEIGHT (in_frame);

  video_area = width * height;

  GST_OBJECT_LOCK (filter);
  if (filter->feedback) {
    stride_mask = 0xfcfcfcfc;
    stride = 8;
    stride_shift = 2;
  } else {
    stride_mask = 0xf8f8f8f8;
    stride = 4;
    stride_shift = 3;
  }

  for (i = 0; i < video_area; i++) {
    planetable[plane][i] = (src[i] & stride_mask) >> stride_shift;
  }

  cf = plane & (stride - 1);
  if (filter->feedback) {
    for (i = 0; i < video_area; i++) {
      dest[i] = planetable[cf][i]
          + planetable[cf + stride][i]
          + planetable[cf + stride * 2][i]
          + planetable[cf + stride * 3][i];
      planetable[plane][i] = (dest[i] & stride_mask) >> stride_shift;
    }
  } else {
    for (i = 0; i < video_area; i++) {
      dest[i] = planetable[cf][i]
          + planetable[cf + stride][i]
          + planetable[cf + stride * 2][i]
          + planetable[cf + stride * 3][i]
          + planetable[cf + stride * 4][i]
          + planetable[cf + stride * 5][i]
          + planetable[cf + stride * 6][i]
          + planetable[cf + stride * 7][i];
    }
  }

  plane++;
  filter->plane = plane & (PLANES - 1);
  GST_OBJECT_UNLOCK (filter);

  return GST_FLOW_OK;
}
