ffmpeg_rescale_video( void )
{
  if( video_resize_ctx && ( frm_w != res_w || frm_h != res_h ) ) {
    sws_freeContext( video_resize_ctx );
    video_resize_ctx = NULL;
    res_w = -1;
    ffmpeg_pict = ff_picture;
  }

  if( res_w == -1 ) {
    ff_tmp_picture = alloc_picture( out_pix_fmt, out_w, out_h, NULL );
    if( !ff_tmp_picture ) {
      printe( "FFMPEG: Could not allocate temporary picture\n" );
      avcodec_close( video_st->codec );
      av_free( ff_picture );
      return 1;
    }
    res_w = frm_w;
    res_h = frm_h;
  }
  if( video_resize_ctx == NULL ) {
    video_resize_ctx = sws_getContext( res_w, res_h,
                                      PIX_FMT_YUV444P,
                                      out_w, out_h,
                                      out_pix_fmt,
                                      sws_flags, NULL, NULL, NULL );
    if( !video_resize_ctx ) {
      printe( "Cannot initialize the conversion context\n" );
      avcodec_close( video_st->codec );
      av_free( ff_picture );
      return 1;
    }
    ffmpeg_pict = ff_tmp_picture;
  }
  sws_scale( video_resize_ctx,
		(const uint8_t * const*)ff_picture->data, ff_picture->linesize,
		0, res_h, ff_tmp_picture->data, ff_tmp_picture->linesize );
  printi( 3, "ffmpeg_rescale_frame(): resize %dx%d -> %dx%d pix format %d->%d\n", frm_w, frm_h, out_w, out_h, PIX_FMT_YUV444P, out_pix_fmt );
  return 0;
}
