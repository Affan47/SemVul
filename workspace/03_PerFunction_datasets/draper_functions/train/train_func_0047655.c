bgav_demuxer_next_packet(bgav_demuxer_context_t * demuxer)
  {
  int ret = 0, i;

  switch(demuxer->demux_mode)
    {
    case DEMUX_MODE_SI_I:
      if(bgav_track_eof_d(demuxer->tt->cur))
        return 0;

      ret = bgav_demuxer_next_packet_interleaved(demuxer);
      if(!ret)
        bgav_track_set_eof_d(demuxer->tt->cur);

      break;
    case DEMUX_MODE_SI_NI:
      if(demuxer->request_stream->flags & STREAM_EOF_D)
        return 0;
      ret = next_packet_noninterleaved(demuxer);
      if(!ret)
        demuxer->request_stream->flags |= STREAM_EOF_D;
      break;
    case DEMUX_MODE_FI:
      ret = bgav_demuxer_next_packet_fileindex(demuxer);
      if(!ret)
        demuxer->request_stream->flags |= STREAM_EOF_D;
      break;
    case DEMUX_MODE_STREAM:
      ret = demuxer->demuxer->next_packet(demuxer);

      if(!ret)
        {


        for(i = 0; i < demuxer->tt->cur->num_audio_streams; i++)
          {
          if(demuxer->tt->cur->audio_streams[i].packet)
            {
            bgav_stream_done_packet_write(&demuxer->tt->cur->audio_streams[i],
                                          demuxer->tt->cur->audio_streams[i].packet);
            demuxer->tt->cur->audio_streams[i].packet = NULL;
            ret = 1;
            }
          }
        for(i = 0; i < demuxer->tt->cur->num_video_streams; i++)
          {
          if(demuxer->tt->cur->video_streams[i].packet)
            {
            bgav_stream_done_packet_write(&demuxer->tt->cur->video_streams[i],
                                          demuxer->tt->cur->video_streams[i].packet);
            demuxer->tt->cur->video_streams[i].packet = NULL;
            ret = 1;
            }
          }
        bgav_track_set_eof_d(demuxer->tt->cur);
        }
      break;
    }

  return ret;
  }
