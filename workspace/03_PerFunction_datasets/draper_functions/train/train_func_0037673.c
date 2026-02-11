gegl_tile_handler_command (GeglTileSource *gegl_tile_source,
                           GeglTileCommand command,
                           gint            x,
                           gint            y,
                           gint            z,
                           gpointer        data)
{
  GeglTileHandler *handler = (GeglTileHandler*)gegl_tile_source;

  return gegl_tile_handler_source_command (handler, command, x, y, z, data);
}
