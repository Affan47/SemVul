read_metadata(bgav_demuxer_context_t * ctx)
  {
  char * str = NULL;
  uint16_t len1, len2, len3, len4, len5;
  int str_len;
  bgav_charset_converter_t * cnv = NULL;

  if(!bgav_input_read_16_le(ctx->input, &len1) ||
     !bgav_input_read_16_le(ctx->input, &len2) ||
     !bgav_input_read_16_le(ctx->input, &len3) ||
     !bgav_input_read_16_le(ctx->input, &len4) ||
     !bgav_input_read_16_le(ctx->input, &len5))
    goto fail;

  cnv = bgav_charset_converter_create(ctx->opt, "UTF-16LE", "UTF-8");

  str_len = len1;
  if(str_len < len2)
    str_len = len2;
  if(str_len < len3)
    str_len = len3;
  if(str_len < len4)
    str_len = len4;
  if(str_len < len5)
    str_len = len5;

  str = malloc(str_len);


  if(len1)
    {
    if(bgav_input_read_data(ctx->input, (uint8_t*)str, len1) < len1)
      goto fail;
    gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                            GAVL_META_TITLE, bgav_convert_string(cnv, str, len1,
                                                                 NULL));
    }


  if(len2)
    {
    if(bgav_input_read_data(ctx->input, (uint8_t*)str, len2) < len2)
      goto fail;
    gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                            GAVL_META_AUTHOR, bgav_convert_string(cnv, str, len2,
                                                                  NULL));
    }


  if(len3)
    {
    if(bgav_input_read_data(ctx->input, (uint8_t*)str, len3) < len3)
      goto fail;
    gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                            GAVL_META_COPYRIGHT, bgav_convert_string(cnv, str, len3,
                                                                     NULL));
    }


  if(len4)
    {
    if(bgav_input_read_data(ctx->input, (uint8_t*)str, len4) < len4)
      goto fail;
    gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                            GAVL_META_COMMENT, bgav_convert_string(cnv, str, len4,
                                                                   NULL));
    }


  if(len5)
    bgav_input_skip(ctx->input, len5);

  free(str);
  bgav_charset_converter_destroy(cnv);
  return 1;

  fail:
  if(cnv)
    bgav_charset_converter_destroy(cnv);
  if(str)
    free(str);
  return 0;
  }
