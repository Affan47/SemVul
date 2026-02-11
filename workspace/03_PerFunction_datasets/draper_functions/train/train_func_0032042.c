decode_openjpeg(bgav_stream_t * s, gavl_video_frame_t * f)
  {
  openjpeg_priv_t * priv;
  bgav_packet_t * p;
  opj_cio_t *cio;

  priv = s->data.video.decoder->priv;

  if(!(s->flags & STREAM_HAVE_PICTURE))
    {
    p = bgav_stream_get_packet_read(s);
    if(!p)
      return 0;
    }
  else
    p = NULL;

  if(f || priv->need_format)
    {
    if(!(s->flags & STREAM_HAVE_PICTURE))
      {

      cio = opj_cio_open((opj_common_ptr)priv->dinfo,
                         p->data, p->data_size);

      priv->img = opj_decode(priv->dinfo, cio);


      opj_cio_close(cio);

      if(priv->need_format)
        {
        s->data.video.format.image_width  = priv->img->x1 - priv->img->x0;
        s->data.video.format.image_height = priv->img->y1 - priv->img->y0;
        s->data.video.format.image_width  /= (1 << s->opt->shrink);
        s->data.video.format.image_height /= (1 << s->opt->shrink);

        s->data.video.format.frame_width  = s->data.video.format.image_width;
        s->data.video.format.frame_height = s->data.video.format.image_height;


        if(s->fourcc == BGAV_MK_FOURCC('R', '3', 'D', '1'))
          {
          s->data.video.format.pixelformat = GAVL_RGB_48;
          }
        }
      s->flags |= STREAM_HAVE_PICTURE;
      }
    if(f)
      {
      if(s->fourcc == BGAV_MK_FOURCC('R', '3', 'D', '1'))
        {
        int i;
        int* planes[4];
        for(i = 0; i < 4; i++)
          planes[i] = priv->img->comps[i].data;


        redcode_ycbcr2rgb(planes, priv->img->comps[0].w,
                          priv->img->comps[0].h,
                          (uint16_t*)f->planes[0], f->strides[0]);

        f->timestamp = p->pts;
        f->duration = p->duration;
        }
      else
        {

        }
      opj_image_destroy(priv->img);
      }

    }
  if(p)
    bgav_stream_done_packet_read(s, p);

  return 1;
  }
