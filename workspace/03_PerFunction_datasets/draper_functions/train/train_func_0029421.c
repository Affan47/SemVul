gst_tta_parse_src_event (GstPad * pad, GstEvent * event)
{
  GstTtaParse *ttaparse = GST_TTA_PARSE (GST_PAD_PARENT (pad));

  gboolean res = TRUE;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:
    {
      gdouble rate;
      GstFormat format;
      GstSeekFlags flags;
      GstSeekType start_type, stop_type;
      gint64 start, stop;

      gst_event_parse_seek (event, &rate, &format, &flags,
          &start_type, &start, &stop_type, &stop);

      if (format == GST_FORMAT_TIME) {
        if (flags & GST_SEEK_FLAG_FLUSH) {
          gst_pad_push_event (ttaparse->srcpad, gst_event_new_flush_start ());
          gst_pad_push_event (ttaparse->sinkpad, gst_event_new_flush_start ());
        } else {
          gst_pad_pause_task (ttaparse->sinkpad);
        }
        GST_PAD_STREAM_LOCK (ttaparse->sinkpad);

        switch (start_type) {
          case GST_SEEK_TYPE_CUR:
            ttaparse->current_frame += (start / GST_SECOND) / FRAME_TIME;
            break;
          case GST_SEEK_TYPE_END:
            ttaparse->current_frame += (start / GST_SECOND) / FRAME_TIME;
            break;
          case GST_SEEK_TYPE_SET:
            ttaparse->current_frame = (start / GST_SECOND) / FRAME_TIME;
            break;
          case GST_SEEK_TYPE_NONE:
            break;
        }
        res = TRUE;

        if (flags & GST_SEEK_FLAG_FLUSH) {
          gst_pad_push_event (ttaparse->srcpad, gst_event_new_flush_stop ());
          gst_pad_push_event (ttaparse->sinkpad, gst_event_new_flush_stop ());
        }

        gst_pad_push_event (ttaparse->srcpad, gst_event_new_new_segment (FALSE,
                1.0, GST_FORMAT_TIME, 0,
                ttaparse->num_frames * FRAME_TIME * GST_SECOND, 0));

        gst_pad_start_task (ttaparse->sinkpad,
            (GstTaskFunction) gst_tta_parse_loop, ttaparse);

        GST_PAD_STREAM_UNLOCK (ttaparse->sinkpad);

      } else {
        res = FALSE;
      }

      gst_event_unref (event);
      break;
    }
    default:
      res = gst_pad_event_default (pad, event);
      break;
  }

  return res;
}
