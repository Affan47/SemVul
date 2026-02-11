add_video_stream( enum CodecID codec_id, int w, int h, int timing )
{
  AVCodecContext *c;

#ifdef HAVE_FFMPEG_AVFORMAT_NEW_STREAM
  video_st = avformat_new_stream( oc, NULL );
#else
  video_st = av_new_stream( oc, 0 );
#endif

  if( !video_st ) {
    printe( "FFMPEG: Could not allocate video stream\n" );
    return 1;
  }

  c = video_st->codec;
  c->codec_id = codec_id;
  c->codec_type = AVMEDIA_TYPE_VIDEO;


  if( ffmpeg_vrate > 0 )
    c->bit_rate = ffmpeg_vrate;
  else if( ffmpeg_vrate == 0 )
    c->bit_rate = c->bit_rate * VRATE_MULT;


  c->width  = w;
  c->height = h;


  c->gop_size = 25;
  video_st->sample_aspect_ratio = c->sample_aspect_ratio = ffmpeg_aspect;
  if( ffmpeg_libx264 ) {
    c->profile = FF_PROFILE_H264_HIGH;
    c->me_range = 16;
    c->max_qdiff = 4;
    c->qmin = 10;
    c->qmax = 51;
#ifndef HAVE_FFMPEG_AVDICTIONARY
    c->crf = 23;
    c->cqp = -1;
#endif
    c->qcompress = 0.0;
    c->me_method = 8;
    c->trellis = 1;


    c->flags2 |= 0;
  }

  if( oc->oformat->flags & AVFMT_GLOBALHEADER )
    c->flags |= CODEC_FLAG_GLOBAL_HEADER;
  return 0;
}
