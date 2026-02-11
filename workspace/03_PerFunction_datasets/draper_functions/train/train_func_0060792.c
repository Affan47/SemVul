gst_dilate_transform_frame (GstVideoFilter * vfilter,
    GstVideoFrame * in_frame, GstVideoFrame * out_frame)
{
  GstDilate *filter = GST_DILATE (vfilter);
  gint video_size, width, height;
  gboolean erode;
  guint32 *src, *dest;
  GstClockTime timestamp;
  gint64 stream_time;

  src = GST_VIDEO_FRAME_PLANE_DATA (in_frame, 0);
  dest = GST_VIDEO_FRAME_PLANE_DATA (out_frame, 0);

  width = GST_VIDEO_FRAME_WIDTH (in_frame);
  height = GST_VIDEO_FRAME_HEIGHT (in_frame);


  timestamp = GST_BUFFER_TIMESTAMP (in_frame->buffer);
  stream_time =
      gst_segment_to_stream_time (&GST_BASE_TRANSFORM (filter)->segment,
      GST_FORMAT_TIME, timestamp);

  GST_DEBUG_OBJECT (filter, "sync to %" GST_TIME_FORMAT,
      GST_TIME_ARGS (timestamp));

  if (GST_CLOCK_TIME_IS_VALID (stream_time))
    gst_object_sync_values (GST_OBJECT (filter), stream_time);

  GST_OBJECT_LOCK (filter);
  erode = filter->erode;
  GST_OBJECT_UNLOCK (filter);

  video_size = width * height;
  transform (src, dest, video_size, width, height, erode);

  return GST_FLOW_OK;
}
