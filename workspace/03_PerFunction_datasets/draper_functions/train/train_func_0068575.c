free_tracks(bgav_edl_track_t * s, int len)
  {
  int i;
  for(i = 0; i < len; i++)
    {
    if(s[i].metadata)
      {
      gavl_metadata_free(s[i].metadata);
      free(s[i].metadata);
      }
    if(s[i].name)
      free(s[i].name);

    if(s[i].audio_streams)
      free_streams(s[i].audio_streams, s[i].num_audio_streams);
    if(s[i].video_streams)
      free_streams(s[i].video_streams, s[i].num_video_streams);
    if(s[i].subtitle_text_streams)
      free_streams(s[i].subtitle_text_streams, s[i].num_subtitle_text_streams);
    if(s[i].subtitle_overlay_streams)
      free_streams(s[i].subtitle_overlay_streams, s[i].num_subtitle_overlay_streams);
    }
  free(s);
  }
