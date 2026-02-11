gst_agingtv_transform_frame (GstVideoFilter * filter, GstVideoFrame * in_frame,
    GstVideoFrame * out_frame)
{
  GstAgingTV *agingtv = GST_AGINGTV (filter);
  gint area_scale;
  GstClockTime timestamp, stream_time;
  gint width, height, stride, video_size;
  guint32 *src, *dest;

  timestamp = GST_BUFFER_TIMESTAMP (in_frame->buffer);
  stream_time =
      gst_segment_to_stream_time (&GST_BASE_TRANSFORM (filter)->segment,
      GST_FORMAT_TIME, timestamp);

  GST_DEBUG_OBJECT (agingtv, "sync to %" GST_TIME_FORMAT,
      GST_TIME_ARGS (timestamp));

  if (GST_CLOCK_TIME_IS_VALID (stream_time))
    gst_object_sync_values (GST_OBJECT (agingtv), stream_time);

  width = GST_VIDEO_FRAME_WIDTH (in_frame);
  height = GST_VIDEO_FRAME_HEIGHT (in_frame);
  stride = GST_VIDEO_FRAME_PLANE_STRIDE (in_frame, 0);
  video_size = stride * height / 4;

  src = GST_VIDEO_FRAME_PLANE_DATA (in_frame, 0);
  dest = GST_VIDEO_FRAME_PLANE_DATA (out_frame, 0);

  area_scale = width * height / 64 / 480;
  if (area_scale <= 0)
    area_scale = 1;

  if (agingtv->color_aging)
    coloraging (src, dest, video_size, &agingtv->coloraging_state);
  else
    memcpy (dest, src, video_size);

  scratching (agingtv->scratches, agingtv->scratch_lines, dest, width, height);
  if (agingtv->pits)
    pits (dest, width, height, area_scale, &agingtv->pits_interval);
  if (area_scale > 1 && agingtv->dusts)
    dusts (dest, width, height, &agingtv->dust_interval, area_scale);

  return GST_FLOW_OK;
}
