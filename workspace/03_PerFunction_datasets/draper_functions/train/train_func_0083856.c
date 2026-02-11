bgav_track_remove_unsupported(bgav_track_t * track)
  {
  int i;
  bgav_stream_t * s;

  i = 0;
  while(i < track->num_audio_streams)
    {
    s = &track->audio_streams[i];
    if(!bgav_find_audio_decoder(s))
      {
      bgav_track_remove_audio_stream(track, i);

      if(!(s->fourcc & 0xffff0000))
        bgav_log(s->opt, BGAV_LOG_WARNING, LOG_DOMAIN,
                 "No audio decoder found for WAVId 0x%04x",
                 s->fourcc);
      else
        bgav_log(s->opt, BGAV_LOG_WARNING, LOG_DOMAIN,
                 "No audio decoder found for fourcc %c%c%c%c (0x%08x)",
                 (s->fourcc & 0xFF000000) >> 24,
                 (s->fourcc & 0x00FF0000) >> 16,
                 (s->fourcc & 0x0000FF00) >> 8,
                 (s->fourcc & 0x000000FF),
                 s->fourcc);
      }
    else if((s->flags & STREAM_PARSE_FULL) &&
       !bgav_audio_parser_supported(s->fourcc))
      bgav_track_remove_audio_stream(track, i);
    else
      i++;
    }
  i = 0;
  while(i < track->num_video_streams)
    {
    s = &track->video_streams[i];
    if(!bgav_find_video_decoder(s))
      {
      bgav_log(s->opt, BGAV_LOG_WARNING, LOG_DOMAIN,
               "No video decoder found for fourcc %c%c%c%c (0x%08x)",
               (s->fourcc & 0xFF000000) >> 24,
               (s->fourcc & 0x00FF0000) >> 16,
               (s->fourcc & 0x0000FF00) >> 8,
               (s->fourcc & 0x000000FF),
               s->fourcc);
      bgav_track_remove_video_stream(track, i);
      }
    else if((s->flags & (STREAM_PARSE_FULL|STREAM_PARSE_FRAME)) &&
       !bgav_video_parser_supported(s->fourcc))
      {
      bgav_log(s->opt, BGAV_LOG_WARNING, LOG_DOMAIN,
               "No parser found for fourcc %c%c%c%c (0x%08x)",
               (s->fourcc & 0xFF000000) >> 24,
               (s->fourcc & 0x00FF0000) >> 16,
               (s->fourcc & 0x0000FF00) >> 8,
               (s->fourcc & 0x000000FF),
               s->fourcc);
      bgav_track_remove_video_stream(track, i);
      }
    else
      i++;
    }
  }
