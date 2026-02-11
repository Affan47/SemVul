bgav_mkv_tracks_read(bgav_input_context_t * ctx,
                         bgav_mkv_track_t ** ret1,
                         int * ret_num1,
                         bgav_mkv_element_t * parent)
  {
  bgav_mkv_track_t * ret = NULL;
  int ret_num = 0;

  bgav_mkv_element_t e;
  while(ctx->position < parent->end)
    {
    if(!bgav_mkv_element_read(ctx, &e))
      return 0;

    switch(e.id)
      {
      case MKV_ID_TrackEntry:
        ret = realloc(ret, (ret_num+1)*sizeof(*ret));
        memset(ret + ret_num, 0, sizeof(*ret));
        if(!bgav_mkv_track_read(ctx, ret + ret_num, &e))
          return 0;


        ret_num++;
        break;
      default:
        bgav_mkv_element_skip(ctx, &e, "tracks");
        break;
      }
    }
  *ret1 = ret;
  *ret_num1 = ret_num;
  return 1;
  }
