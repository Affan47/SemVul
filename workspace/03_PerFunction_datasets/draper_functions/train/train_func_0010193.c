VP8LColorSpaceTransform(int width, int height, int bits, int step,
                             uint32_t* const argb, uint32_t* image) {
  const int max_tile_size = 1 << bits;
  int tile_xsize = VP8LSubSampleSize(width, bits);
  int tile_ysize = VP8LSubSampleSize(height, bits);
  int accumulated_red_histo[256] = { 0 };
  int accumulated_blue_histo[256] = { 0 };
  int tile_y;
  int tile_x;
  Multipliers prevX;
  Multipliers prevY;
  MultipliersClear(&prevY);
  MultipliersClear(&prevX);
  for (tile_y = 0; tile_y < tile_ysize; ++tile_y) {
    for (tile_x = 0; tile_x < tile_xsize; ++tile_x) {
      Multipliers color_transform;
      int all_x_max;
      int y;
      const int tile_y_offset = tile_y * max_tile_size;
      const int tile_x_offset = tile_x * max_tile_size;
      if (tile_y != 0) {
        ColorCodeToMultipliers(image[tile_y * tile_xsize + tile_x - 1], &prevX);
        ColorCodeToMultipliers(image[(tile_y - 1) * tile_xsize + tile_x],
                               &prevY);
      } else if (tile_x != 0) {
        ColorCodeToMultipliers(image[tile_y * tile_xsize + tile_x - 1], &prevX);
      }
      color_transform =
          GetBestColorTransformForTile(tile_x, tile_y, bits,
                                       prevX, prevY,
                                       step, width, height,
                                       &accumulated_red_histo[0],
                                       &accumulated_blue_histo[0],
                                       argb);
      image[tile_y * tile_xsize + tile_x] =
          MultipliersToColorCode(&color_transform);
      CopyTileWithColorTransform(width, height, tile_x, tile_y, bits,
                                 color_transform, argb);


      all_x_max = tile_x_offset + max_tile_size;
      if (all_x_max > width) {
        all_x_max = width;
      }
      for (y = 0; y < max_tile_size; ++y) {
        int ix;
        int all_x;
        int all_y = tile_y_offset + y;
        if (all_y >= height) {
          break;
        }
        ix = all_y * width + tile_x_offset;
        for (all_x = tile_x_offset; all_x < all_x_max; ++all_x, ++ix) {
          if (ix >= 2 &&
              argb[ix] == argb[ix - 2] &&
              argb[ix] == argb[ix - 1]) {
            continue;
          }
          if (ix >= width + 2 &&
              argb[ix - 2] == argb[ix - width - 2] &&
              argb[ix - 1] == argb[ix - width - 1] &&
              argb[ix] == argb[ix - width]) {
            continue;
          }
          ++accumulated_red_histo[(argb[ix] >> 16) & 0xff];
          ++accumulated_blue_histo[argb[ix] & 0xff];
        }
      }
    }
  }
}
