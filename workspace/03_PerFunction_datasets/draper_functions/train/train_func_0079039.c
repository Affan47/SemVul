ColorSpaceInverseTransform(const VP8LTransform* const transform,
                                       int y_start, int y_end, uint32_t* data) {
  const int width = transform->xsize_;
  const int tile_width = 1 << transform->bits_;
  const int mask = tile_width - 1;
  const int safe_width = width & ~mask;
  const int remaining_width = width - safe_width;
  const int tiles_per_row = VP8LSubSampleSize(width, transform->bits_);
  int y = y_start;
  const uint32_t* pred_row =
      transform->data_ + (y >> transform->bits_) * tiles_per_row;

  while (y < y_end) {
    const uint32_t* pred = pred_row;
    VP8LMultipliers m = { 0, 0, 0 };
    const uint32_t* const data_safe_end = data + safe_width;
    const uint32_t* const data_end = data + width;
    while (data < data_safe_end) {
      ColorCodeToMultipliers(*pred++, &m);
      VP8LTransformColorInverse(&m, data, tile_width);
      data += tile_width;
    }
    if (data < data_end) {
      ColorCodeToMultipliers(*pred++, &m);
      VP8LTransformColorInverse(&m, data, remaining_width);
      data += remaining_width;
    }
    ++y;
    if ((y & mask) == 0) pred_row += tiles_per_row;
  }
}
