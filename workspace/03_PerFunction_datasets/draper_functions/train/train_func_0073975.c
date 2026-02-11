gst_video_test_src_do_seek (GstBaseSrc * bsrc, GstSegment * segment)
{
  GstClockTime time;
  GstVideoTestSrc *src;

  src = GST_VIDEO_TEST_SRC (bsrc);

  segment->time = segment->start;
  time = segment->last_stop;


  if (src->rate_numerator) {
    src->n_frames = gst_util_uint64_scale (time,
        src->rate_numerator, src->rate_denominator * GST_SECOND);
  } else {
    src->n_frames = 0;
  }
  if (src->rate_numerator) {
    src->running_time = gst_util_uint64_scale (src->n_frames,
        src->rate_denominator * GST_SECOND, src->rate_numerator);
  } else {

    src->running_time = 0;
  }

  g_assert (src->running_time <= time);

  return TRUE;
}
