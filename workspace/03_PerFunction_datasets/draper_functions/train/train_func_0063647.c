set_pts(bgav_stream_t * s, stream_priv_t * sp,
                    bgav_packet_t * p)
  {
  if(s->type == BGAV_STREAM_VIDEO)
    {
    p->pts = sp->pts_counter;
    p->duration = s->data.video.format.frame_duration;
    sp->pts_counter += p->duration;
    if(sp->frame_size)
      PACKET_SET_KEYFRAME(p);
    }
  else if(s->type == BGAV_STREAM_AUDIO)
    {
    p->pts = sp->pts_counter;
    if(s->data.audio.block_align)
      p->duration = p->data_size / s->data.audio.block_align;
    sp->pts_counter += p->duration;
    PACKET_SET_KEYFRAME(p);
    }
  }
