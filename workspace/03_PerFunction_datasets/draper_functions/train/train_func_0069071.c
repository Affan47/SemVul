theora_parse_src_query (GstPad * pad, GstObject * parent, GstQuery * query)
{
  GstTheoraParse *parse;
  gboolean res = FALSE;

  parse = GST_THEORA_PARSE (parent);

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:
    {
      gint64 frame, value;
      GstFormat my_format, format;
      gint64 time;

      frame = parse->prev_frame;

      GST_LOG_OBJECT (parse,
          "query %p: we have current frame: %" G_GINT64_FORMAT, query, frame);


      gst_query_parse_position (query, &format, NULL);


      my_format = GST_FORMAT_TIME;
      if (!(res =
              theora_parse_src_convert (parse->sinkpad, GST_FORMAT_DEFAULT,
                  frame, &my_format, &time)))
        goto error;


      GST_LOG_OBJECT (parse,
          "query %p: our time: %" GST_TIME_FORMAT " (conv to %s)",
          query, GST_TIME_ARGS (time), gst_format_get_name (format));

      if (!(res =
              theora_parse_src_convert (pad, my_format, time, &format, &value)))
        goto error;

      gst_query_set_position (query, format, value);

      GST_LOG_OBJECT (parse,
          "query %p: we return %" G_GINT64_FORMAT " (format %u)", query, value,
          format);

      break;
    }
    case GST_QUERY_DURATION:

      if (!(res = gst_pad_query (GST_PAD_PEER (parse->sinkpad), query)))
        goto error;
      break;
    case GST_QUERY_CONVERT:
    {
      GstFormat src_fmt, dest_fmt;
      gint64 src_val, dest_val;

      gst_query_parse_convert (query, &src_fmt, &src_val, &dest_fmt, &dest_val);
      if (!(res =
              theora_parse_src_convert (pad, src_fmt, src_val, &dest_fmt,
                  &dest_val)))
        goto error;

      gst_query_set_convert (query, src_fmt, src_val, dest_fmt, dest_val);
      break;
    }
    default:
      res = gst_pad_query_default (pad, parent, query);
      break;
  }
done:

  return res;


error:
  {
    GST_DEBUG_OBJECT (parse, "query failed");
    goto done;
  }
}
