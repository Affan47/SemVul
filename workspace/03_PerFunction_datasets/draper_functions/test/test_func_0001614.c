gegl_buffer_linear_new_from_data (const gpointer       data,
                                  const Babl          *format,
                                  const GeglRectangle *extent,
                                  gint                 rowstride,
                                  GDestroyNotify       destroy_fn,
                                  gpointer             destroy_fn_data)
{
  GeglBuffer *buffer;

  g_assert (format);

  if (rowstride <= 0)


    rowstride = extent->width;
  else
    rowstride = rowstride / babl_format_get_bytes_per_pixel (format);
    buffer = gegl_buffer_linear_new2 (extent, format, rowstride);

  {
    GeglTile *tile = gegl_tile_new_bare ();

    tile->tile_storage = buffer->tile_storage;
    tile->x = 0;
    tile->y = 0;
    tile->z = 0;
    tile->next_shared = tile;
    tile->prev_shared = tile;
    gegl_tile_set_data_full (tile,
                             (gpointer) data,
                             babl_format_get_bytes_per_pixel (format) * rowstride * extent->height,
                             destroy_fn,
                             destroy_fn_data);

    if (buffer->tile_storage->cache)
      gegl_tile_handler_cache_insert (buffer->tile_storage->cache, tile, 0, 0, 0);
    gegl_tile_unref (tile);
  }

  return buffer;
}
