WebPAllocateDecBuffer(int w, int h,
                                    const WebPDecoderOptions* const options,
                                    WebPDecBuffer* const out) {
  if (out == NULL || w <= 0 || h <= 0) {
    return VP8_STATUS_INVALID_PARAM;
  }
  if (options != NULL) {
    if (options->use_cropping) {
      const int cw = options->crop_width;
      const int ch = options->crop_height;
      const int x = options->crop_left & ~1;
      const int y = options->crop_top & ~1;
      if (x < 0 || y < 0 || cw <= 0 || ch <= 0 || x + cw > w || y + ch > h) {
        return VP8_STATUS_INVALID_PARAM;
      }
      w = cw;
      h = ch;
    }
    if (options->use_scaling) {
      if (options->scaled_width <= 0 || options->scaled_height <= 0) {
        return VP8_STATUS_INVALID_PARAM;
      }
      w = options->scaled_width;
      h = options->scaled_height;
    }
  }
  out->width = w;
  out->height = h;


  return AllocateBuffer(out);
}
