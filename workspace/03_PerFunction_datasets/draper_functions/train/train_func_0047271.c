exr_save_process (const float       *pixels,
                  int                w,
                  int                h,
                  int                d,
                  int                tile_size,
                  const std::string &filename)
{
  if (tile_size == 0)
    {

      write_scanline_exr (pixels, w, h, d, filename);
    }
  else
    {

      write_tiled_exr (pixels, w, h, d, tile_size, tile_size, filename);
    }
}
