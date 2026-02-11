MBAnalyzeBestIntra16Mode(VP8EncIterator* const it) {
  const int max_mode =
      (it->enc_->method_ >= FAST_ANALYSIS_METHOD) ? MAX_INTRA16_MODE
                                                  : NUM_PRED_MODES;
  int mode;
  int best_alpha = DEFAULT_ALPHA;
  int best_mode = 0;

  VP8MakeLuma16Preds(it);
  for (mode = 0; mode < max_mode; ++mode) {
    VP8Histogram histo = { { 0 } };
    int alpha;

    VP8CollectHistogram(it->yuv_in_ + Y_OFF,
                        it->yuv_p_ + VP8I16ModeOffsets[mode],
                        0, 16, &histo);
    alpha = GetAlpha(&histo);
    if (IS_BETTER_ALPHA(alpha, best_alpha)) {
      best_alpha = alpha;
      best_mode = mode;
    }
  }
  VP8SetIntra16Mode(it, best_mode);
  return best_alpha;
}
