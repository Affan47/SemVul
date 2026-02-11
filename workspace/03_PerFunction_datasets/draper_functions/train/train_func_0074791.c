decode_rtjpeg(bgav_stream_t * s, gavl_video_frame_t * f)
  {
  rtjpeg_priv_t * priv;
  bgav_packet_t * p;
  priv = s->data.video.decoder->priv;


  p = bgav_stream_get_packet_read(s);
  if(!p)
    return 0;


  if(!f)
    {
    bgav_stream_done_packet_read(s, p);
    return 1;
    }

  RTjpeg_decompress(priv->rtjpeg, p->data, priv->frame->planes);
  gavl_video_frame_copy(&s->data.video.format,
                        f, priv->frame);

  f->timestamp = p->pts;
  f->duration = p->duration;

  bgav_stream_done_packet_read(s, p);
  return 1;
  }
