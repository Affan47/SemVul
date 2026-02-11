MBAnalyzeBestUVMode(VP8EncIterator* const it) {
  int best_alpha = DEFAULT_ALPHA;
  int best_mode = 0;
  const int max_mode = MAX_UV_MODE;
  int mode;

  VP8MakeChroma8Preds(it);
  for (mode = 0; mode < max_mode; ++mode) {
    VP8Histogram histo = { { 0 } };
    int alpha;
    VP8CollectHistogram(it->yuv_in_ + U_OFF,
                        it->yuv_p_ + VP8UVModeOffsets[mode],
                        16, 16 + 4 + 4, &histo);
    alpha = GetAlpha(&histo);
    if (IS_BETTER_ALPHA(alpha, best_alpha)) {
      best_alpha = alpha;
      best_mode = mode;
    }
  }
  VP8SetIntraUVMode(it, best_mode);
  return best_alpha;
}
