add_audio_stream( enum CodecID codec_id, int freq, int stereo )
{
  AVCodecContext *c;

#ifdef HAVE_FFMPEG_AVFORMAT_NEW_STREAM
  audio_st = avformat_new_stream( oc, NULL );
#else
  audio_st = av_new_stream( oc, 1 );
#endif

  if( !audio_st ) {
    printe( "FFMPEG: Could not allocate audio stream stream\n" );
    return 1;
  }

#ifdef HAVE_FFMPEG_AVFORMAT_NEW_STREAM
  audio_st->id = 1;
#endif

  c = audio_st->codec;
  c->codec_id = codec_id;
  c->codec_type = AVMEDIA_TYPE_AUDIO;


  c->sample_fmt = AV_SAMPLE_FMT_S16;
  if( ffmpeg_arate > 0 )
    c->bit_rate = ffmpeg_arate;
  audio_resample_ctx = NULL;

  c->sample_rate = out_rte;
  c->channels = out_chn;


  if( oc->oformat->flags & AVFMT_GLOBALHEADER )
    c->flags |= CODEC_FLAG_GLOBAL_HEADER;

  return 0;
}
