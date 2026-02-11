gst_dvd_sub_parse_chain (GstPad * pad, GstBuffer * buf)
{
  GstDvdSubParse *parse = GST_DVD_SUB_PARSE (GST_PAD_PARENT (pad));
  GstAdapter *adapter;
  GstBuffer *outbuf = NULL;
  GstFlowReturn ret = GST_FLOW_OK;

  adapter = parse->adapter;

  GST_LOG_OBJECT (parse, "%4u bytes, ts: %" GST_TIME_FORMAT,
      GST_BUFFER_SIZE (buf), GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buf)));

  gst_adapter_push (adapter, buf);

  if (!parse->needed) {
    const guint8 *data;

    data = gst_adapter_peek (adapter, 2);
    parse->needed = GST_READ_UINT16_BE (data);
  }

  if (GST_BUFFER_TIMESTAMP_IS_VALID (buf)) {
    if (GST_CLOCK_TIME_IS_VALID (parse->stamp))

      GST_WARNING_OBJECT (parse, "Received more timestamps than expected.");
    else
      parse->stamp = GST_BUFFER_TIMESTAMP (buf);
  }

  if (parse->needed) {
    guint av;

    av = gst_adapter_available (adapter);
    if (av >= parse->needed) {
      if (av > parse->needed) {

        GST_WARNING_OBJECT (parse, "Unexpected: needed %d, "
            "but more (%d) is available.", parse->needed, av);
      }
      outbuf = gst_adapter_take_buffer (adapter, parse->needed);

      gst_buffer_set_caps (outbuf, GST_PAD_CAPS (parse->srcpad));
      GST_BUFFER_TIMESTAMP (outbuf) = parse->stamp;

      parse->stamp = GST_CLOCK_TIME_NONE;
      parse->needed = 0;

      ret = gst_pad_push (parse->srcpad, outbuf);
    }
  }

  return ret;
}
