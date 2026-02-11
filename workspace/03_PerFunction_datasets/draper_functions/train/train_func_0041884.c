bgav_video_parser_check_output(bgav_video_parser_t * parser)
  {
#if 0
  fprintf(stderr, "check output cs: %d fp: %d sz: %d pts: %lld skip: %d\n",
          parser->cache_size, parser->cache[0].field_pic,
          parser->cache[0].size, parser->cache[0].pts,
          parser->cache[0].skip);
#endif
  if(parser->cache_size && !parser->cache[0].field_pic &&
     parser->cache[0].size &&
     ((parser->cache[0].pts != BGAV_TIMESTAMP_UNDEFINED) ||
      parser->cache[0].skip))
    return 1;
  return 0;
  }
