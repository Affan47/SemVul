gst_pes_filter_process (GstPESFilter * filter)
{
  GstFlowReturn ret;
  gboolean skip = FALSE;

  g_return_val_if_fail (filter != NULL, GST_FLOW_ERROR);

  switch (filter->state) {
    case STATE_HEADER_PARSE:
      ret = gst_pes_filter_parse (filter);
      break;
    case STATE_DATA_SKIP:
      skip = TRUE;

    case STATE_DATA_PUSH:
      if (filter->length > 0 || filter->unbounded_packet) {
        gint avail;

        avail = gst_adapter_available (filter->adapter);
        if (filter->unbounded_packet == FALSE)
          avail = MIN (avail, filter->length);

        if (skip) {
          gst_adapter_flush (filter->adapter, avail);
          ADAPTER_OFFSET_FLUSH (avail);
          ret = GST_FLOW_OK;
        } else {
          GstBuffer *out;

          out = gst_adapter_take_buffer (filter->adapter, avail);

          ret = gst_pes_filter_data_push (filter, filter->first, out);
          filter->first = FALSE;
        }

        if (filter->unbounded_packet == FALSE) {
          filter->length -= avail;
          if (filter->length == 0)
            filter->state = STATE_HEADER_PARSE;
        }
      } else {
        filter->state = STATE_HEADER_PARSE;
        ret = GST_FLOW_OK;
      }
      break;
    default:
      goto wrong_state;
  }
  return ret;


wrong_state:
  {
    GST_DEBUG ("wrong internal state %d", filter->state);
    return GST_FLOW_ERROR;
  }
}
