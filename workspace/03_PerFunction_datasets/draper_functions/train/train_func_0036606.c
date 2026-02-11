gegl_tile_backend_file_command (GeglTileSource  *self,
                                GeglTileCommand  command,
                                gint             x,
                                gint             y,
                                gint             z,
                                gpointer         data)
{
  switch (command)
    {
      case GEGL_TILE_GET:
        return gegl_tile_backend_file_get_tile (self, x, y, z);
      case GEGL_TILE_SET:
        return gegl_tile_backend_file_set_tile (self, data, x, y, z);

      case GEGL_TILE_IDLE:
        return NULL;


      case GEGL_TILE_VOID:
        return gegl_tile_backend_file_void_tile (self, data, x, y, z);

      case GEGL_TILE_EXIST:
        return gegl_tile_backend_file_exist_tile (self, data, x, y, z);
      case GEGL_TILE_FLUSH:
        return gegl_tile_backend_file_flush (self, data, x, y, z);

      default:
        g_assert (command < GEGL_TILE_LAST_COMMAND &&
                  command >= 0);
    }
  return FALSE;
}
