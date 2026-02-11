bgav_audio_resync(bgav_stream_t * s)
  {
  s->data.audio.frame->valid_samples = 0;

  if(s->out_time == BGAV_TIMESTAMP_UNDEFINED)
    {
    s->out_time =
      gavl_time_rescale(s->timescale,
                        s->data.audio.format.samplerate,
                        STREAM_GET_SYNC(s));
    }

  if(s->data.audio.parser)
    {
    bgav_audio_parser_reset(s->data.audio.parser,
                            BGAV_TIMESTAMP_UNDEFINED, s->out_time);
    }
  if(s->data.audio.decoder &&
     s->data.audio.decoder->decoder->resync)
    s->data.audio.decoder->decoder->resync(s);
  }
