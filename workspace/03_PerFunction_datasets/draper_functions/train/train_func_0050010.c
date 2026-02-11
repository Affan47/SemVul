gst_dvd_sub_dec_chain (GstPad * pad, GstObject * parent, GstBuffer * buf)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstDvdSubDec *dec;
  guint8 *data;
  glong size = 0;

  dec = GST_DVD_SUB_DEC (parent);

  GST_DEBUG_OBJECT (dec, "Have buffer of size %" G_GSIZE_FORMAT ", ts %"
      GST_TIME_FORMAT ", dur %" G_GINT64_FORMAT, gst_buffer_get_size (buf),
      GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buf)), GST_BUFFER_DURATION (buf));

  if (GST_BUFFER_TIMESTAMP_IS_VALID (buf)) {
    if (!GST_CLOCK_TIME_IS_VALID (dec->next_ts)) {
      dec->next_ts = GST_BUFFER_TIMESTAMP (buf);
    }


    ret = gst_dvd_sub_dec_advance_time (dec, GST_BUFFER_TIMESTAMP (buf));
  }

  if (dec->have_title) {
    gst_buffer_unmap (dec->partialbuf, &dec->partialmap);
    gst_buffer_unref (dec->partialbuf);
    dec->partialbuf = NULL;
    dec->have_title = FALSE;
  }

  GST_DEBUG_OBJECT (dec, "Got subtitle buffer, pts %" GST_TIME_FORMAT,
      GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buf)));


  if (dec->partialbuf) {
    gst_buffer_unmap (dec->partialbuf, &dec->partialmap);
    dec->partialbuf = gst_buffer_append (dec->partialbuf, buf);
  } else {
    dec->partialbuf = buf;
  }

  gst_buffer_map (dec->partialbuf, &dec->partialmap, GST_MAP_READ);

  data = dec->partialmap.data;
  size = dec->partialmap.size;

  if (size > 4) {
    dec->packet_size = GST_READ_UINT16_BE (data);

    if (dec->packet_size == size) {
      GST_LOG_OBJECT (dec, "Subtitle packet size %d, current size %ld",
          dec->packet_size, size);

      dec->data_size = GST_READ_UINT16_BE (data + 2);


      dec->parse_pos = data;
      dec->forced_display = FALSE;
      dec->visible = FALSE;

      dec->have_title = TRUE;
      dec->next_event_ts = GST_BUFFER_TIMESTAMP (dec->partialbuf);

      if (!GST_CLOCK_TIME_IS_VALID (dec->next_event_ts))
        dec->next_event_ts = dec->next_ts;

      dec->next_event_ts += gst_dvd_sub_dec_get_event_delay (dec);
    }
  }

  return ret;
}
