add_subtitle_stream(bgav_track_t * t,
                                           const bgav_options_t * opt,
                                           int text,
                                           const char * charset,
                                           bgav_subtitle_reader_context_t * r)
  {
  bgav_stream_t * ret;

  t->num_subtitle_streams++;
  t->subtitle_streams = realloc(t->subtitle_streams, t->num_subtitle_streams *
                                sizeof(*(t->subtitle_streams)));

  ret = &t->subtitle_streams[t->num_subtitle_streams-1];
  bgav_stream_init(ret, opt);
  if(!r)
    bgav_stream_create_packet_buffer(ret);
  else
    ret->data.subtitle.subreader = r;

  if(text)
    {
    ret->type = BGAV_STREAM_SUBTITLE_TEXT;
    if(charset)
      ret->data.subtitle.charset = bgav_strdup(charset);
    }
  else
    ret->type = BGAV_STREAM_SUBTITLE_OVERLAY;

  ret->track = t;

  return ret;
  }
