bgav_seek_scaled(bgav_t * b, int64_t * time, int scale)
  {
  int i;
  bgav_track_t * track = b->tt->cur;


  bgav_track_clear_eof_d(track);
  b->eof = 0;


  if(b->demuxer->si && !(b->demuxer->flags & BGAV_DEMUXER_SI_PRIVATE_FUNCS))
    {
    seek_si(b, b->demuxer, *time, scale);
    }

  else if(b->tt->cur->flags & TRACK_SAMPLE_ACCURATE)
    {
    seek_sa(b, time, scale);
    }

  else if(!(b->demuxer->flags & BGAV_DEMUXER_SEEK_ITERATIVE))
    {
    seek_once(b, time, scale);
    }

  else
    {
    seek_iterative(b, time, scale);
    }


  for(i = 0; i < track->num_subtitle_streams; i++)
    {
    if(track->subtitle_streams[i].data.subtitle.subreader &&
       track->subtitle_streams[i].action != BGAV_STREAM_MUTE)
      {

      track->subtitle_streams[i].flags &= ~(STREAM_EOF_C|STREAM_EOF_D);
      bgav_subtitle_reader_seek(&track->subtitle_streams[i],
                                *time, scale);
      }
    }


  }
