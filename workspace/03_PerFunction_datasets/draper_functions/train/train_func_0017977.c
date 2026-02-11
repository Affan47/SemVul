set_half (GeglTile   * dst_tile,
                             GeglTile   * src_tile,
                             gint         width,
                             gint         height,
                             const Babl * format,
                             gint i,
                             gint j)
{
  guchar *dst_data   = gegl_tile_get_data (dst_tile);
  guchar *src_data   = gegl_tile_get_data (src_tile);
  gint    components = babl_format_get_n_components (format);
  gint    bpp        = babl_format_get_bytes_per_pixel (format);

  if (i) dst_data += bpp * width / 2;
  if (j) dst_data += bpp * width * height / 2;

  if (babl_format_get_type (format, 0) == babl_type ("float"))
    {
      downscale_float (components, width, height, width * bpp, src_data, dst_data);
    }
  else if (babl_format_get_type (format, 0) == babl_type ("u8"))
    {
      downscale_u8 (components, width, height, width * bpp, src_data, dst_data);
    }
  else
    {
      set_half_nearest (dst_tile, src_tile, width, height, format, i, j);
    }
}
