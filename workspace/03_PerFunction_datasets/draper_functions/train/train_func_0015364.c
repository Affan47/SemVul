PrintFullLosslessInfo(const WebPAuxStats* const stats,
                                  const char* const description) {
  fprintf(stderr, "Lossless-%s compressed size: %d bytes\n",
          description, stats->lossless_size);
  fprintf(stderr, "  * Header size: %d bytes, image data size: %d\n",
          stats->lossless_hdr_size, stats->lossless_data_size);
  if (stats->lossless_features) {
    fprintf(stderr, "  * Lossless features used:");
    if (stats->lossless_features & 1) fprintf(stderr, " PREDICTION");
    if (stats->lossless_features & 2) fprintf(stderr, " CROSS-COLOR-TRANSFORM");
    if (stats->lossless_features & 4) fprintf(stderr, " SUBTRACT-GREEN");
    if (stats->lossless_features & 8) fprintf(stderr, " PALETTE");
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "  * Precision Bits: histogram=%d transform=%d cache=%d\n",
          stats->histogram_bits, stats->transform_bits, stats->cache_bits);
  if (stats->palette_size > 0) {
    fprintf(stderr, "  * Palette size:   %d\n", stats->palette_size);
  }
}
