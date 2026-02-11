bgav_set_subtitle_stream(bgav_t * b, int stream, bgav_stream_action_t action)
  {
  if((stream >= b->tt->cur->num_subtitle_streams) || (stream < 0))
    return 0;
  b->tt->cur->subtitle_streams[stream].action = action;
  return 1;
  }
