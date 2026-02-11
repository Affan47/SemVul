close_mpegps(bgav_demuxer_context_t * ctx)
  {
  mpegps_priv_t * priv;
  priv = ctx->priv;
  if(!priv)
    return;
  if(priv->sector_buffer)
    free(priv->sector_buffer);
  if(priv->input_mem)
    {
    bgav_input_close(priv->input_mem);
    bgav_input_destroy(priv->input_mem);
    }
  free(priv);
  }
