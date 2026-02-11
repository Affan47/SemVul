close_mpegts(bgav_demuxer_context_t * ctx)
  {
  int i;
  mpegts_t * priv;
  priv = ctx->priv;

  if(!priv)
    return;

  if(priv->input_mem)
    {
    bgav_input_close(priv->input_mem);
    bgav_input_destroy(priv->input_mem);
    }
  if(priv->buffer)
    free(priv->buffer);
  if(priv->programs)
    {
    for(i = 0; i < priv->num_programs; i++)
      {
      if(priv->programs[i].streams)
        free(priv->programs[i].streams);
      }
    free(priv->programs);
    }
  free(priv);
  }
