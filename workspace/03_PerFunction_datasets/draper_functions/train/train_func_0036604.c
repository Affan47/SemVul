bgav_BITMAPINFOHEADER_get_format(bgav_BITMAPINFOHEADER_t * bh,
                                      bgav_stream_t * s)
  {
  s->data.video.format.frame_width  = bh->biWidth;
  s->data.video.format.frame_height = bh->biHeight;

  s->data.video.format.image_width  = bh->biWidth;
  s->data.video.format.image_height = bh->biHeight;

  s->data.video.format.pixel_width  = 1;
  s->data.video.format.pixel_height = 1;
  s->data.video.depth               = bh->biBitCount;
  s->data.video.image_size          = bh->biSizeImage;
  s->data.video.planes              = bh->biPlanes;

  s->fourcc = bgav_BITMAPINFOHEADER_get_fourcc(bh);


  if(!s->fourcc)
    s->fourcc = BGAV_MK_FOURCC('R', 'G', 'B', ' ');
  }
