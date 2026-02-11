gegl_tile_backend_ram_command (GeglTileSource     *tile_store,
                               GeglTileCommand command,
                               gint            x,
                               gint            y,
                               gint            z,
                               gpointer        data)
{
  switch (command)
    {
      case GEGL_TILE_GET:
        return get_tile (tile_store, x, y, z);

      case GEGL_TILE_SET:
        set_tile (tile_store, data, x, y, z);
        return NULL;

      case GEGL_TILE_IDLE:
        return NULL;

      case GEGL_TILE_VOID:
        void_tile (tile_store, data, x, y, z);
        return NULL;

      case GEGL_TILE_EXIST:
        return GINT_TO_POINTER(exist_tile (tile_store, data, x, y, z));

      default:
        g_assert (command < GEGL_TILE_LAST_COMMAND &&
                  command >= 0);
    }
  return FALSE;
}
