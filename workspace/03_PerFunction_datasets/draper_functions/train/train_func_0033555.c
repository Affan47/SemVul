gegl_tile_store (GeglTile *tile)
{
  if (gegl_tile_is_stored (tile))
    return TRUE;
  if (tile->tile_storage == NULL)
    return FALSE;
  return gegl_tile_source_set_tile (GEGL_TILE_SOURCE (tile->tile_storage),
                                    tile->x,
                                    tile->y,
                                    tile->z,
                                    tile);
}
