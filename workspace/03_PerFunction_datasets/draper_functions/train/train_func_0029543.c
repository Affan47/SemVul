gst_sub_parse_src_event (GstPad * pad, GstEvent * event)
{
  GstSubParse *self = GST_SUBPARSE (gst_pad_get_parent (pad));
  gboolean ret = FALSE;

  GST_DEBUG ("Handling %s event", GST_EVENT_TYPE_NAME (event));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:
    {
      GstFormat format;
      GstSeekType start_type, stop_type;
      gint64 start, stop;
      gdouble rate;
      gboolean update;

      gst_event_parse_seek (event, &rate, &format, &self->segment_flags,
          &start_type, &start, &stop_type, &stop);

      if (format != GST_FORMAT_TIME) {
        GST_WARNING_OBJECT (self, "we only support seeking in TIME format");
        gst_event_unref (event);
        goto beach;
      }


      ret = gst_pad_push_event (self->sinkpad,
          gst_event_new_seek (rate, GST_FORMAT_BYTES, self->segment_flags,
              GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_NONE, 0));

      if (ret) {

        gst_segment_set_seek (&self->segment, rate, format, self->segment_flags,
            start_type, start, stop_type, stop, &update);

        GST_DEBUG_OBJECT (self, "segment after seek: %" GST_SEGMENT_FORMAT,
            &self->segment);

        self->next_offset = 0;

        self->need_segment = TRUE;
      } else {
        GST_WARNING_OBJECT (self, "seek to 0 bytes failed");
      }

      gst_event_unref (event);
      break;
    }
    default:
      ret = gst_pad_event_default (pad, event);
      break;
  }

beach:
  gst_object_unref (self);

  return ret;
}
