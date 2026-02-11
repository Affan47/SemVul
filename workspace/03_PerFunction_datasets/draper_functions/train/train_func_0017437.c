mpegtsmux_src_event (GstPad * pad, GstEvent * event)
{
  MpegTsMux *mux = GST_MPEG_TSMUX (gst_pad_get_parent (pad));
  gboolean res = TRUE;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CUSTOM_UPSTREAM:
    {
      GstIterator *iter;
      GstIteratorResult iter_ret;
      GstPad *sinkpad;
      GstClockTime running_time;
      gboolean all_headers, done;
      guint count;

      if (!gst_video_event_is_force_key_unit (event))
        break;

      gst_video_event_parse_upstream_force_key_unit (event,
          &running_time, &all_headers, &count);

      GST_INFO_OBJECT (mux, "received upstream force-key-unit event, "
          "seqnum %d running_time %" GST_TIME_FORMAT " all_headers %d count %d",
          gst_event_get_seqnum (event), GST_TIME_ARGS (running_time),
          all_headers, count);

      if (!all_headers)
        break;

      mux->pending_key_unit_ts = running_time;
      gst_event_replace (&mux->force_key_unit_event, event);

      iter = gst_element_iterate_sink_pads (GST_ELEMENT_CAST (mux));
      done = FALSE;
      while (!done) {
        gboolean res = FALSE, tmp;
        iter_ret = gst_iterator_next (iter, (gpointer *) & sinkpad);

        switch (iter_ret) {
          case GST_ITERATOR_DONE:
            done = TRUE;
            break;
          case GST_ITERATOR_OK:
            GST_INFO_OBJECT (mux, "forwarding to %s",
                gst_pad_get_name (sinkpad));
            tmp = gst_pad_push_event (sinkpad, gst_event_ref (event));
            GST_INFO_OBJECT (mux, "result %d", tmp);

            res |= tmp;
            gst_object_unref (sinkpad);
            break;
          case GST_ITERATOR_ERROR:
            done = TRUE;
            break;
          case GST_ITERATOR_RESYNC:
            break;
        }
      }

      gst_event_unref (event);
      break;
    }
    default:
      res = gst_pad_event_default (pad, event);
      break;
  }

  gst_object_unref (mux);
  return res;
}
