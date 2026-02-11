close_r3d(bgav_demuxer_context_t * ctx)
  {
  r3d_priv_t * priv;
  priv = ctx->priv;

  if(priv->rdvo) free(priv->rdvo);
  if(priv->rdvs) free(priv->rdvs);
  if(priv->rdao) free(priv->rdao);
  if(priv->rdas) free(priv->rdas);

  free(priv);
  }
