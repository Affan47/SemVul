add_audio_stream_compressed_theora(void * data,
                                              const gavl_metadata_t * m,
                                              const gavl_audio_format_t * format,
                                              const gavl_compression_info_t * ci)
  {
  int ret;
  ret = bg_ogg_encoder_add_audio_stream_compressed(data, format, ci);
  if(ci->id == GAVL_CODEC_ID_VORBIS)
    bg_ogg_encoder_init_audio_stream(data, ret, &bg_vorbis_codec);
  return ret;
  }
