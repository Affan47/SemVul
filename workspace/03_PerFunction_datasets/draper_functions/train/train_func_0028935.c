bgav_read_audio(bgav_t * b, gavl_audio_frame_t * frame,
                    int stream, int num_samples)
  {
  bgav_stream_t * s = &b->tt->cur->audio_streams[stream];

  if(b->eof)
    return 0;

  return read_audio(s, frame, num_samples);
  }
