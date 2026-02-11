get_tile_size (ChamplainMapSource *map_source)
{
  ChamplainMapSourceChain *source_chain = CHAMPLAIN_MAP_SOURCE_CHAIN (map_source);

  g_return_val_if_fail (source_chain, 0);

  ChamplainMapSourceChainPrivate *priv = source_chain->priv;
  g_return_val_if_fail (priv->stack_top, 0);

  return champlain_map_source_get_tile_size (priv->stack_top);
}
