champlain_map_source_get_meters_per_pixel (ChamplainMapSource *map_source,
    guint zoom_level,
    gdouble latitude,
    G_GNUC_UNUSED gdouble longitude)
{
  g_return_val_if_fail (CHAMPLAIN_IS_MAP_SOURCE (map_source), 0.0);


  gdouble tile_size = champlain_map_source_get_tile_size (map_source);

  return 2.0 *M_PI *EARTH_RADIUS *sin (M_PI / 2.0 - M_PI / 180.0 *latitude) /
         (tile_size * champlain_map_source_get_row_count (map_source, zoom_level));
}
