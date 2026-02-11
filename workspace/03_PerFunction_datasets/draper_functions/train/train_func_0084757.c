handle_stepping (GstBaseSink * sink, GstSegment * segment,
    GstStepInfo * current, guint64 * cstart, guint64 * cstop, guint64 * rstart,
    guint64 * rstop)
{
  gboolean step_end = FALSE;


  if (current->amount == -1)
    return FALSE;


  switch (current->format) {
    case GST_FORMAT_TIME:
    {
      guint64 end;
      guint64 first, last;
      gdouble abs_rate;

      if (segment->rate > 0.0) {
        if (segment->stop == *cstop)
          *rstop = *rstart + current->amount;

        first = *rstart;
        last = *rstop;
      } else {
        if (segment->start == *cstart)
          *rstart = *rstop + current->amount;

        first = *rstop;
        last = *rstart;
      }

      end = current->start + current->amount;
      current->position = first - current->start;

      abs_rate = ABS (segment->rate);
      if (G_UNLIKELY (abs_rate != 1.0))
        current->position /= abs_rate;

      GST_DEBUG_OBJECT (sink,
          "buffer: %" GST_TIME_FORMAT "-%" GST_TIME_FORMAT,
          GST_TIME_ARGS (first), GST_TIME_ARGS (last));
      GST_DEBUG_OBJECT (sink,
          "got time step %" GST_TIME_FORMAT "-%" GST_TIME_FORMAT "/%"
          GST_TIME_FORMAT, GST_TIME_ARGS (current->position),
          GST_TIME_ARGS (last - current->start),
          GST_TIME_ARGS (current->amount));

      if ((current->flush && current->position >= current->amount)
          || last >= end) {
        GST_DEBUG_OBJECT (sink, "step ended, we need clipping");
        step_end = TRUE;
        if (segment->rate > 0.0) {
          *rstart = end;
          *cstart = gst_segment_to_position (segment, GST_FORMAT_TIME, end);
        } else {
          *rstop = end;
          *cstop = gst_segment_to_position (segment, GST_FORMAT_TIME, end);
        }
      }
      GST_DEBUG_OBJECT (sink,
          "cstart %" GST_TIME_FORMAT ", rstart %" GST_TIME_FORMAT,
          GST_TIME_ARGS (*cstart), GST_TIME_ARGS (*rstart));
      GST_DEBUG_OBJECT (sink,
          "cstop %" GST_TIME_FORMAT ", rstop %" GST_TIME_FORMAT,
          GST_TIME_ARGS (*cstop), GST_TIME_ARGS (*rstop));
      break;
    }
    case GST_FORMAT_BUFFERS:
      GST_DEBUG_OBJECT (sink,
          "got default step %" G_GUINT64_FORMAT "/%" G_GUINT64_FORMAT,
          current->position, current->amount);

      if (current->position < current->amount) {
        current->position++;
      } else {
        step_end = TRUE;
      }
      break;
    case GST_FORMAT_DEFAULT:
    default:
      GST_DEBUG_OBJECT (sink,
          "got unknown step %" G_GUINT64_FORMAT "/%" G_GUINT64_FORMAT,
          current->position, current->amount);
      break;
  }
  return step_end;
}
