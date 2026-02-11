HistogramAdd(const VP8LHistogram* const in,
                         VP8LHistogram* const out) {
  int i;
  for (i = 0; i < PIX_OR_COPY_CODES_MAX; ++i) {
    out->literal_[i] += in->literal_[i];
  }
  for (i = 0; i < NUM_DISTANCE_CODES; ++i) {
    out->distance_[i] += in->distance_[i];
  }
  for (i = 0; i < 256; ++i) {
    out->red_[i] += in->red_[i];
    out->blue_[i] += in->blue_[i];
    out->alpha_[i] += in->alpha_[i];
  }
}
