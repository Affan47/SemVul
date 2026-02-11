bgav_audio_parser_init_flac(bgav_audio_parser_t * parser)
  {
  flac_priv_t * priv;


  if(parser->s->ext_size != 42)
    {
    bgav_log(parser->s->opt, BGAV_LOG_ERROR, LOG_DOMAIN,
             "Corrupted flac header");
    return;
    }

  priv = calloc(1, sizeof(*priv));
  parser->priv = priv;


  bgav_flac_streaminfo_read(parser->s->ext_data + 8, &priv->si);

  parser->parse_frame = parse_frame_flac;
  parser->cleanup = cleanup_flac;
  }
