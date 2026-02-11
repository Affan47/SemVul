start_video(bg_ogg_encoder_t * e, int stream)
  {
  bg_ogg_video_stream_t * s = &e->video_streams[stream];

  if(s->ci)
    {
    if(!s->codec->init_video_compressed(s->codec_priv,
                                        &s->format,
                                        s->ci,
                                        &e->metadata))
      return 0;

    }
  else
    {
    if(!s->codec->init_video(s->codec_priv,
                             &s->format,
                             &e->metadata))
      return 0;

    if(s->pass)
      {
      if(!s->codec->set_video_pass)
        return 0;

      else
        if(!s->codec->set_video_pass(s->codec_priv,
                                     s->pass,
                                     s->total_passes,
                                     s->stats_file))
          return 0;
      }
    }

  return 1;
  }
