VP8LCalculateEstimateForCacheSize(const uint32_t* const argb,
                                      int xsize, int ysize,
                                      int* const best_cache_bits) {
  int ok = 0;
  int cache_bits;
  double lowest_entropy = 1e99;
  VP8LBackwardRefs refs;
  static const double kSmallPenaltyForLargeCache = 4.0;
  static const int quality = 30;
  if (!VP8LBackwardRefsAlloc(&refs, xsize * ysize) ||
      !BackwardReferencesHashChain(xsize, ysize, argb, 0, quality, &refs)) {
    goto Error;
  }
  for (cache_bits = 0; cache_bits <= MAX_COLOR_CACHE_BITS; ++cache_bits) {
    double cur_entropy;
    VP8LHistogram histo;
    VP8LHistogramInit(&histo, cache_bits);
    ComputeCacheHistogram(argb, xsize, ysize, &refs, cache_bits, &histo);
    cur_entropy = VP8LHistogramEstimateBits(&histo) +
        kSmallPenaltyForLargeCache * cache_bits;
    if (cache_bits == 0 || cur_entropy < lowest_entropy) {
      *best_cache_bits = cache_bits;
      lowest_entropy = cur_entropy;
    }
  }
  ok = 1;
 Error:
  VP8LClearBackwardRefs(&refs);
  return ok;
}
