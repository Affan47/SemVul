read_metadata(bgav_demuxer_context_t * ctx, flv_tag * t)
  {
  uint8_t u8;
  flv_priv_t * priv;
  int64_t end_pos;
  int ret;

  priv = ctx->priv;

  end_pos = ctx->input->position + t->data_size;

  bgav_input_skip(ctx->input, 13);
  bgav_input_read_data(ctx->input, &u8, 1);
  if(u8 == 8)
    bgav_input_skip(ctx->input, 4);

  priv->metadata.type = TYPE_OBJECT;

  ret = read_meta_object(ctx->input, &priv->metadata, 0, 0, end_pos);

  if(ret && (ctx->input->position < end_pos))
    {
    bgav_input_skip(ctx->input, end_pos - ctx->input->position);
    }
  return ret;
  }
