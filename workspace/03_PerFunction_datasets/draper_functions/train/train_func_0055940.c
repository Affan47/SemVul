bgav_mkv_ebml_header_read(bgav_input_context_t * ctx,
                              bgav_mkv_ebml_header_t * ret)
  {
  bgav_mkv_element_t e;
  bgav_mkv_element_t e1;
  uint64_t tmp_64;


  ret->EBMLVersion      = 1;
  ret->EBMLReadVersion = 1;
  ret->EBMLMaxIDLength     = 4;
  ret->EBMLMaxSizeLength   = 8;

  ret->DocTypeVersion      = 1;
  ret->DocTypeReadVersion = 1;


  if(!bgav_mkv_element_read(ctx, &e))
    return 0;

  if(e.id != MKV_ID_EBML)
    return 0;


  while(ctx->position < e.end)
    {
    if(!bgav_mkv_element_read(ctx, &e1))
      return 0;

    switch(e1.id)
      {
      case MKV_ID_EBMLVersion:
        if(!mkv_read_uint(ctx, &tmp_64, e1.size))
          return 0;
        ret->EBMLVersion = tmp_64;
        break;
      case MKV_ID_EBMLReadVersion:
        if(!mkv_read_uint(ctx, &tmp_64, e1.size))
          return 0;
        ret->EBMLReadVersion = tmp_64;
        break;
      case MKV_ID_EBMLMaxIDLength:
        if(!mkv_read_uint(ctx, &tmp_64, e1.size))
          return 0;
        ret->EBMLMaxIDLength = tmp_64;
        break;
      case MKV_ID_EBMLMaxSizeLength:
        if(!mkv_read_uint(ctx, &tmp_64, e1.size))
          return 0;
        ret->EBMLMaxSizeLength = tmp_64;
        break;
      case MKV_ID_DocType:
        if(!mkv_read_string(ctx, &ret->DocType, e1.size))
          return 0;
        break;
      case MKV_ID_DocTypeVersion:
        if(!mkv_read_uint(ctx, &tmp_64, e1.size))
          return 0;
        ret->DocTypeVersion = tmp_64;
        break;
      case MKV_ID_DocTypeReadVersion:
        if(!mkv_read_uint(ctx, &tmp_64, e1.size))
          return 0;
        ret->DocTypeReadVersion = tmp_64;
        break;
      default:
        bgav_mkv_element_skip(ctx, &e1, "ebml_header");
        break;
      }
    }
  return 1;
  }
