theora_parse_push_headers (GstTheoraParse * parse)
{
  gint i;

  if (!parse->streamheader_received)
    theora_parse_set_streamheader (parse);

  theora_parse_drain_event_queue (parse);


  for (i = 0; i < 3; i++) {
    GstBuffer *buf;

    if ((buf = parse->streamheader[i])) {
      gst_pad_push (parse->srcpad, buf);
      parse->streamheader[i] = NULL;
    }
  }
}
