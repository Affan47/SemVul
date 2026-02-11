gegl_tile_handler_chain_bind (GeglTileHandlerChain *tile_handler_chain)
{
  GSList *iter;

  iter = tile_handler_chain->chain;
  while (iter)
    {
      GeglTileHandler  *handler;
      GeglTileSource *source = NULL;

      handler = iter->data;
      if (iter->next)
        {
          source = iter->next->data;
        }
      else
        {
          source = gegl_tile_handler_get_source (tile_handler_chain);
        }
      gegl_tile_handler_set_source (handler, source);
      iter = iter->next;
    }
}
