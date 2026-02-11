gst_istximage_src_create (GstPushSrc * bs, GstBuffer ** buf)
{
  GstIstXImageSrc *s = GST_ISTXIMAGE_SRC (bs);
  GstIstXImageSrcBuffer *image;
  GstClockTime base_time;
  GstClockTime next_capture_ts;
  GstClockTime dur;
  gint64 next_frame_no;

  if (!gst_istximage_src_recalc (s)) {
    GST_ELEMENT_ERROR (s, RESOURCE, FAILED,
        ("Changing resolution at runtime is not yet supported."), NULL);
    return GST_FLOW_ERROR;
  }

  if (s->fps_n <= 0 || s->fps_d <= 0)
    return GST_FLOW_NOT_NEGOTIATED;


  GST_OBJECT_LOCK (s);
  base_time = GST_ELEMENT_CAST (s)->base_time;
  next_capture_ts = gst_clock_get_time (GST_ELEMENT_CLOCK (s));
  next_capture_ts -= base_time;


  next_frame_no = gst_util_uint64_scale (next_capture_ts,
      s->fps_n, GST_SECOND * s->fps_d);
  if (next_frame_no == s->last_frame_no) {
    GstClockID id;
    GstClockReturn ret;


    next_frame_no += 1;


    next_capture_ts = gst_util_uint64_scale (next_frame_no,
        s->fps_d * GST_SECOND, s->fps_n);

    id = gst_clock_new_single_shot_id (GST_ELEMENT_CLOCK (s),
        next_capture_ts + base_time);
    s->clock_id = id;


    GST_OBJECT_UNLOCK (s);

    GST_DEBUG_OBJECT (s, "Waiting for next frame time %" G_GUINT64_FORMAT,
        next_capture_ts);
    ret = gst_clock_id_wait (id, NULL);
    GST_OBJECT_LOCK (s);

    gst_clock_id_unref (id);
    s->clock_id = NULL;
    if (ret == GST_CLOCK_UNSCHEDULED) {

      GST_OBJECT_UNLOCK (s);
      return GST_FLOW_WRONG_STATE;
    }

    dur = gst_util_uint64_scale_int (GST_SECOND, s->fps_d, s->fps_n);
  } else {
    GstClockTime next_frame_ts;

    GST_DEBUG_OBJECT (s, "No need to wait for next frame time %"
        G_GUINT64_FORMAT " next frame = %" G_GINT64_FORMAT " prev = %"
        G_GINT64_FORMAT, next_capture_ts, next_frame_no, s->last_frame_no);
    next_frame_ts = gst_util_uint64_scale (next_frame_no + 1,
        s->fps_d * GST_SECOND, s->fps_n);

    dur = next_frame_ts - next_capture_ts;
  }
  s->last_frame_no = next_frame_no;
  GST_OBJECT_UNLOCK (s);

  image = gst_istximage_src_ximage_get (s);
  if (!image)
    return GST_FLOW_ERROR;

  *buf = GST_BUFFER (image);
  GST_BUFFER_TIMESTAMP (*buf) = next_capture_ts;
  GST_BUFFER_DURATION (*buf) = dur;

  return GST_FLOW_OK;
}
