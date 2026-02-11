seek_mtv(bgav_demuxer_context_t * ctx, int64_t time, int scale)
  {
  uint32_t file_position;
  uint32_t frame_number;
  bgav_stream_t * s;
  mtv_priv_t * priv;
  priv = ctx->priv;

  frame_number = gavl_time_rescale(scale, priv->video_fps, time);
  file_position = MTV_HEADER_SIZE + priv->sync_size * frame_number;

  bgav_input_seek(ctx->input, file_position, SEEK_SET);

  if(ctx->tt->cur->num_audio_streams)
    {
    s = &ctx->tt->cur->audio_streams[0];

    STREAM_SET_SYNC(s, gavl_time_rescale(priv->video_fps,
                                         s->data.audio.format.samplerate,
                                         frame_number));
    }
  if(ctx->tt->cur->num_video_streams)
    {
    s = &ctx->tt->cur->video_streams[0];
    STREAM_SET_SYNC(s, frame_number);
    ctx->tt->cur->video_streams[0].in_position = frame_number;
    }
  priv->do_audio = 1;
  }
