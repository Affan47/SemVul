ApplyPalette(uint32_t* src, uint32_t* dst,
                         uint32_t src_stride, uint32_t dst_stride,
                         const uint32_t* palette, int palette_size,
                         int width, int height, int xbits, uint8_t* row) {
  int i, x, y;
  int use_LUT = 1;
  for (i = 0; i < palette_size; ++i) {
    if ((palette[i] & 0xffff00ffu) != 0) {
      use_LUT = 0;
      break;
    }
  }

  if (use_LUT) {
    uint8_t inv_palette[MAX_PALETTE_SIZE] = { 0 };
    for (i = 0; i < palette_size; ++i) {
      const int color = (palette[i] >> 8) & 0xff;
      inv_palette[color] = i;
    }
    for (y = 0; y < height; ++y) {
      for (x = 0; x < width; ++x) {
        const int color = (src[x] >> 8) & 0xff;
        row[x] = inv_palette[color];
      }
      VP8LBundleColorMap(row, width, xbits, dst);
      src += src_stride;
      dst += dst_stride;
    }
  } else {

    uint32_t last_pix = palette[0];
    int last_idx = 0;
    for (y = 0; y < height; ++y) {
      for (x = 0; x < width; ++x) {
        const uint32_t pix = src[x];
        if (pix != last_pix) {
          for (i = 0; i < palette_size; ++i) {
            if (pix == palette[i]) {
              last_idx = i;
              last_pix = pix;
              break;
            }
          }
        }
        row[x] = last_idx;
      }
      VP8LBundleColorMap(row, width, xbits, dst);
      src += src_stride;
      dst += dst_stride;
    }
  }
}
