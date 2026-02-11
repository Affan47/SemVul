seek_rmff(bgav_demuxer_context_t * ctx, int64_t time, int scale)
  {
  uint32_t i;
  bgav_stream_t * stream;
  rm_stream_t * rs;
  rm_video_stream_t * vs;
  rm_private_t * rm;
  bgav_track_t * track;
  uint32_t real_time;
  uint32_t position = ~0x0;

  uint32_t start_packet = ~0x00;
  uint32_t end_packet =    0x00;


  rm = ctx->priv;
  track = ctx->tt->cur;

  real_time = gavl_time_rescale(scale, 1000, time);


  for(i = 0; i < track->num_video_streams; i++)
    {
    stream = &track->video_streams[i];
    vs = stream->priv;
    vs->com.index_record = seek_indx(&vs->com.stream->indx, real_time,
                                 &position, &start_packet, &end_packet);
    STREAM_SET_SYNC(stream, vs->com.stream->indx.records[vs->com.index_record].timestamp);

    vs->com.data_pos = vs->com.stream->indx.records[vs->com.index_record].offset;
    vs->pic_num = -1;
    }
  for(i = 0; i < track->num_audio_streams; i++)
    {
    stream = &track->audio_streams[i];
    rs = stream->priv;
    rs->index_record = seek_indx(&rs->stream->indx, real_time,
                                 &position, &start_packet, &end_packet);
    STREAM_SET_SYNC(stream, rs->stream->indx.records[rs->index_record].timestamp);
    rs->data_pos = rs->stream->indx.records[rs->index_record].offset;
    }


  if(!rm->is_multirate)
    {
    bgav_input_seek(ctx->input, position, SEEK_SET);


    rm->do_seek = 1;
    rm->next_packet = start_packet;
    while(rm->next_packet < end_packet)
      next_packet_rmff(ctx);
    rm->do_seek = 0;
    }
  }
