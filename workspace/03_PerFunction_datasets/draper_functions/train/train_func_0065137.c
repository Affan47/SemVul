bgav_audio_parser_get_packet(bgav_audio_parser_t * parser,
                                  bgav_packet_t * p)
  {
  bgav_packet_alloc(p, parser->frame_bytes);
  memcpy(p->data, parser->buf.buffer, parser->frame_bytes);
  p->data_size = parser->frame_bytes;
  bgav_packet_pad(p);
  bgav_audio_parser_flush(parser, parser->frame_bytes);

  if(parser->timestamp == BGAV_TIMESTAMP_UNDEFINED)
    {
    if(parser->frame_pts != BGAV_TIMESTAMP_UNDEFINED)
      parser->timestamp = parser->frame_pts;
    else
      parser->timestamp = 0;
    }
  p->pts = parser->timestamp;
  parser->timestamp += parser->frame_samples;

  p->duration = parser->frame_samples;

  p->dts = BGAV_TIMESTAMP_UNDEFINED;

  p->flags = 0;

  PACKET_SET_KEYFRAME(p);

  p->position = parser->frame_position;


  parser->frame_bytes = 0;

#ifdef DUMP_OUTPUT
  bgav_dprintf("Get packet ");
  bgav_packet_dump(p);
#endif

  }
