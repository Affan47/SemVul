gst_audio_decoder_src_event (GstPad * pad, GstEvent * event)
{
  GstAudioDecoder *dec;
  gboolean res = FALSE;

  dec = GST_AUDIO_DECODER (gst_pad_get_parent (pad));
  if (G_UNLIKELY (dec == NULL)) {
    gst_event_unref (event);
    return FALSE;
  }

  GST_DEBUG_OBJECT (dec, "received event %d, %s", GST_EVENT_TYPE (event),
      GST_EVENT_TYPE_NAME (event));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:
    {
      GstFormat format, tformat;
      gdouble rate;
      GstSeekFlags flags;
      GstSeekType cur_type, stop_type;
      gint64 cur, stop;
      gint64 tcur, tstop;
      guint32 seqnum;

      gst_event_parse_seek (event, &rate, &format, &flags, &cur_type, &cur,
          &stop_type, &stop);
      seqnum = gst_event_get_seqnum (event);


      if ((res = gst_pad_push_event (dec->sinkpad, event)))
        break;


      if (format == GST_FORMAT_TIME) {
        if (gst_audio_decoder_do_byte (dec))
          res = gst_audio_decoder_do_seek (dec, event);
        break;
      }


      tformat = GST_FORMAT_TIME;
      if (!(res = gst_pad_query_convert (pad, format, cur, &tformat, &tcur)))
        goto convert_error;
      if (!(res = gst_pad_query_convert (pad, format, stop, &tformat, &tstop)))
        goto convert_error;


      event = gst_event_new_seek (rate, GST_FORMAT_TIME,
          flags, cur_type, tcur, stop_type, tstop);
      gst_event_set_seqnum (event, seqnum);

      res = gst_pad_push_event (dec->sinkpad, event);
      break;
    }
    default:
      res = gst_pad_push_event (dec->sinkpad, event);
      break;
  }
done:
  gst_object_unref (dec);

  return res;


convert_error:
  {
    GST_DEBUG_OBJECT (dec, "cannot convert start/stop for seek");
    goto done;
  }
}
