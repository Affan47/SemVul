open_4xm(bgav_demuxer_context_t * ctx)
  {
  int done = 0;
  fourxm_chunk_t list_chunk;
  fourxm_chunk_t list_subchunk;
  fourxm_chunk_t chunk;
  fourxm_priv_t * priv;
  float framerate = 25.0;

  priv = calloc(1, sizeof(*priv));
  ctx->priv = priv;


  bgav_input_skip(ctx->input, 12);

  ctx->tt = bgav_track_table_create(1);

  while(!done)
    {
    if(!read_chunk_header(ctx->input, &list_chunk))
      {
      return 0;
      }


    switch(list_chunk.type)
      {
      case ID_HEAD:
        while(ctx->input->position < list_chunk.end_pos)
          {
          if(!read_chunk_header(ctx->input, &list_subchunk))
            return 0;


          switch(list_subchunk.type)
            {
            case ID_HNFO:
              while(ctx->input->position < list_subchunk.end_pos)
                {
                if(!read_chunk_header(ctx->input, &chunk))
                  return 0;


                switch(chunk.fourcc)
                  {
                  case ID_info:
                    {
                    char * tmp_string = calloc(chunk.size+1, 1);
                    if(bgav_input_read_data(ctx->input,
                                            (uint8_t*)tmp_string,
                                            chunk.size) < chunk.size)
                      {
                      free(tmp_string);
                      return 0;
                      }
                    gavl_metadata_set_nocpy(&ctx->tt->cur->metadata,
                                            GAVL_META_COMMENT, tmp_string);
                    }
                    break;
                  case ID_std_:
                    bgav_input_skip(ctx->input, 4);
                    if(!bgav_input_read_float_32_le(ctx->input, &framerate))
                      return 0;
                    break;
                  default:
                    skip_chunk(ctx->input, &chunk);
                    break;
                  }
                }
              break;
            case ID_TRK_:
              while(ctx->input->position < list_subchunk.end_pos)
                {
                if(!read_chunk_header(ctx->input, &chunk))
                  return 0;


                switch(chunk.type)
                  {
                  case ID_VTRK:
                    if(!setup_video_stream(ctx, &chunk, framerate))
                      return 0;
                    break;
                  case ID_STRK:
                    if(!setup_audio_stream(ctx, &chunk))
                      return 0;
                    break;
                  default:
                    skip_chunk(ctx->input, &chunk);
                    break;
                  }
                }
              skip_chunk(ctx->input, &list_subchunk);
              break;
            default:
              skip_chunk(ctx->input, &list_subchunk);
              break;
            }
          }
        break;
      case ID_MOVI:
        priv->movi_end = list_chunk.end_pos;
        done = 1;
        break;
      default:
        skip_chunk(ctx->input, &list_chunk);
        break;
      }
    }
  ctx->data_start = ctx->input->position;
  ctx->flags |= BGAV_DEMUXER_HAS_DATA_START;
  gavl_metadata_set(&ctx->tt->cur->metadata,
                    GAVL_META_FORMAT, "4XM");
  return 1;
  }
