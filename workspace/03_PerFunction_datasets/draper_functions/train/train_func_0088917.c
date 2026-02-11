resync_mpeg2(bgav_stream_t*s)
  {
  mpeg2_priv_t * priv;
  bgav_packet_t * p;
  priv = s->data.video.decoder->priv;

  if(priv->p)
    {
    bgav_stream_done_packet_read(s, priv->p);
    priv->p = NULL;
    }
  priv->non_b_count = 0;
  priv->flags &= ~FLAG_EOF;
  priv->flags |= FLAG_NEED_SEQUENCE;

  bgav_pts_cache_clear(&priv->pts_cache);

  mpeg2_reset(priv->dec, 0);


  if(!(s->flags & STREAM_STILL_MODE))
    {


    while(1)
      {

      p = bgav_stream_peek_packet_read(s, 1);
      if(!p)
        return;

      if(PACKET_GET_KEYFRAME(p))
        {
        s->out_time = p->pts;
        break;
        }

      p = bgav_stream_get_packet_read(s);
      bgav_stream_done_packet_read(s, p);
      }
    }

  }
