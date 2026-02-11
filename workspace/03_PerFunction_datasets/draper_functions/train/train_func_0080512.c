gegl_tile_handler_chain_dispose (GObject *object)
{
  GeglTileHandlerChain *tile_handler_chain = GEGL_TILE_HANDLER_CHAIN (object);
  GSList       *iter;
  GSList       *chain;


  gegl_tile_handler_chain_nuke_cache (tile_handler_chain);


  chain = tile_handler_chain->chain;
  tile_handler_chain->chain = NULL;

  iter = chain;
  while (iter)
    {
      if (iter->data)
        {
          if (G_IS_OBJECT (iter->data))
            g_object_unref (iter->data);
          else
            g_free (iter->data);
        }
      iter = iter->next;
    }

  if (chain)
    g_slist_free (chain);
  chain = NULL;

  G_OBJECT_CLASS (gegl_tile_handler_chain_parent_class)->dispose (object);
}
