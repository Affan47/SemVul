set_blank (GeglTile   *dst_tile,
                              gint        width,
                              gint        height,
                              const Babl *format,
                              gint        i,
                              gint        j)
{
  guchar *dst_data  = gegl_tile_get_data (dst_tile);
  gint    bpp       = babl_format_get_bytes_per_pixel (format);
  gint    rowstride = width * bpp;
  gint    scanline;

  gint    bytes = width * bpp / 2;
  guchar *dst   = dst_data + j * height / 2 * rowstride + i * rowstride / 2;

  for (scanline = 0; scanline < height / 2; scanline++)
    {
      memset (dst, 0x0, bytes);
      dst += rowstride;
    }
}
