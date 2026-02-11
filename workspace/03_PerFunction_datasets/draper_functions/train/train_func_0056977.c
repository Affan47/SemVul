flush_stream_mpeg_audio(bgav_stream_t * s)
  {
  if(!s->data.audio.decoder->decoder->parse)
    return 0;
  s->data.audio.decoder->decoder->parse(s);
  return 1;
  }
