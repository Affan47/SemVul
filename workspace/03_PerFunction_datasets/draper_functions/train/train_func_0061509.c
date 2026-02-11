gst_flups_demux_sink_event (GstPad * pad, GstEvent * event)
{
  gboolean res = TRUE;
  GstFluPSDemux *demux;

  demux = GST_FLUPS_DEMUX (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_FLUSH_START:
      gst_flups_demux_send_event (demux, event);
      break;
    case GST_EVENT_FLUSH_STOP:
      gst_flups_demux_send_event (demux, event);
      gst_segment_init (&demux->sink_segment, GST_FORMAT_UNDEFINED);
      gst_flups_demux_flush (demux);
      break;
    case GST_EVENT_NEWSEGMENT:
    {
      gboolean update;
      gdouble rate;
      GstFormat format;
      gint64 start, stop, time;


      gst_flups_demux_close_segment (demux);

      {
        gdouble arate;

        gst_event_parse_new_segment_full (event, &update, &rate, &arate,
            &format, &start, &stop, &time);
        gst_segment_set_newsegment_full (&demux->sink_segment, update, rate,
            arate, format, start, stop, time);

        if (format == GST_FORMAT_BYTES && demux->scr_rate_n != G_MAXUINT64
            && demux->scr_rate_d != G_MAXUINT64) {

          gst_segment_set_newsegment_full (&demux->src_segment, update, rate,
              arate, GST_FORMAT_TIME, BYTES_TO_GSTTIME (start),
              BYTES_TO_GSTTIME (stop), BYTES_TO_GSTTIME (time));
        }

      }

      GST_INFO_OBJECT (demux, "received new segment: rate %g "
          "format %d, start: %" G_GINT64_FORMAT ", stop: %" G_GINT64_FORMAT
          ", time: %" G_GINT64_FORMAT, rate, format, start, stop, time);


      gst_flups_demux_mark_discont (demux, TRUE, TRUE);
      gst_event_unref (event);

      break;
    }
    case GST_EVENT_EOS:
      GST_INFO_OBJECT (demux, "Received EOS");
      if (!gst_flups_demux_send_event (demux, event)
          && !have_open_streams (demux)) {
        GST_WARNING_OBJECT (demux, "EOS and no streams open");
        GST_ELEMENT_ERROR (demux, STREAM, FAILED,
            ("Internal data stream error."), ("No valid streams detected"));
      }
      break;
    case GST_EVENT_CUSTOM_DOWNSTREAM:
    case GST_EVENT_CUSTOM_DOWNSTREAM_OOB:
    {
      const GstStructure *structure = gst_event_get_structure (event);

      if (structure != NULL
          && gst_structure_has_name (structure, "application/x-gst-dvd")) {
        res = gst_flups_demux_handle_dvd_event (demux, event);
      } else {
        gst_flups_demux_send_event (demux, event);
      }
      break;
    }
    default:
      gst_flups_demux_send_event (demux, event);
      break;
  }

  gst_object_unref (demux);

  return res;
}
