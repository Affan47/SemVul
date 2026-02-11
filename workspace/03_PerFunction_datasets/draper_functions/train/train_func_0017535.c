read_meta_data(bgav_demuxer_context_t * ctx, chunk_header_t * ret)
  {
  char * buffer;
  buffer = calloc(1, ret->size + 1);

  if(!bgav_input_read_data(ctx->input, (uint8_t*)buffer, ret->size))
    return 0;

  switch(ret->fourcc)
    {
    case ID_NAME:
      gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                              GAVL_META_TITLE, buffer);
      break;
    case ID_COPY:
      gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                              GAVL_META_COPYRIGHT, buffer);
      break;
    case ID_AUTH:
      gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                              GAVL_META_AUTHOR, buffer);
      break;
    case ID_ANNO:
      gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                              GAVL_META_COMMENT, buffer);
      break;
    }
  return 1;
  }
