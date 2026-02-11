bgav_build_file_index_si_parse(bgav_t * b)
  {
  int i, j;
  for(i = 0; i < b->tt->num_tracks; i++)
    {
    b->demuxer->flags |= BGAV_DEMUXER_BUILD_INDEX;
    for(j = 0; j < b->tt->cur->num_audio_streams; j++)
      {
      if(!b->tt->cur->audio_streams[j].index_mode)
        continue;

      if(!build_file_index_si_parse_audio(b, i, j))
        return 0;
      }
    for(j = 0; j < b->tt->cur->num_video_streams; j++)
      {
      if(!b->tt->cur->video_streams[j].index_mode)
        continue;

      if(!build_file_index_si_parse_video(b, i, j))
        return 0;
      }
    b->demuxer->flags &= ~BGAV_DEMUXER_BUILD_INDEX;
    }
  return 1;
  }
