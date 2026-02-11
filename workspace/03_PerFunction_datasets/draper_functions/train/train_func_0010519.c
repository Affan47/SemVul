get_tile (GeglTileSource *tile_store,
          gint            x,
          gint            y,
          gint            z)
{
  GeglTileBackendTileDir     *tile_backend_tiledir = GEGL_TILE_BACKEND_TILE_DIR (tile_store);
  GeglTileBackend *backend  = GEGL_TILE_BACKEND (tile_store);
  GeglTile        *tile     = NULL;

 if (exist_tile (tile_store, NULL, x, y, z))
  {
    GioEntry       entry;
    gint   tile_size = gegl_tile_backend_get_tile_size (backend);

    entry.x = x;
    entry.y = y;
    entry.z = z;

    tile = gegl_tile_new (tile_size);

    gio_entry_read (tile_backend_tiledir, &entry, gegl_tile_get_data (tile));
    return tile;
  }
 return NULL;
}
