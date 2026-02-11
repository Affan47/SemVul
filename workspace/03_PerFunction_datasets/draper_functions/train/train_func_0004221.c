gst_segment_to_position (GstSegment * segment, GstFormat format,
    gint64 running_time)
{
  gint64 result;
  gint64 start, stop, accum;

  g_return_val_if_fail (segment != NULL, -1);

  if (G_UNLIKELY (running_time == -1))
    return -1;

  if (G_UNLIKELY (segment->format == GST_FORMAT_UNDEFINED))
    segment->format = format;


  if (G_LIKELY (segment->format == format)) {
    start = segment->start;
    stop = segment->stop;
    accum = segment->accum;
  } else {
    start = 0;
    stop = -1;
    accum = 0;
  }


  if (running_time < accum)
    return -1;


  result = running_time - accum;


  if (G_UNLIKELY (segment->abs_rate != 1.0))
    result = ceil (result * segment->abs_rate);

  if (G_LIKELY (segment->rate > 0.0)) {

    result += start;


    if (G_UNLIKELY (stop != -1 && result > stop))
      return -1;
  } else {


    if (G_UNLIKELY (stop == -1 || result + start > stop))
      return -1;


    result = stop - result;
  }
  return result;
}
