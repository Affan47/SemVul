gegl_buffer_get_tile (GeglTileSource *source,
                      gint        x,
                      gint        y,
                      gint        z)
{
  GeglTileHandler *handler = GEGL_TILE_HANDLER (source);
  GeglTile    *tile   = NULL;
  source = handler->source;

  if (source)
    tile = gegl_tile_source_get_tile (source, x, y, z);
  else
    g_assert (0);

  if (tile)
    {
      GeglBuffer *buffer = GEGL_BUFFER (handler);


      {
        if (!tile->tile_storage)
          {
            gegl_tile_lock (tile);
            tile->tile_storage = buffer->tile_storage;
            gegl_tile_unlock (tile);
            tile->rev--;
          }
        tile->x = x;
        tile->y = y;
        tile->z = z;
      }
    }

  return tile;
}
