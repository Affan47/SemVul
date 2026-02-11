VP8AdjustFilterStrength(VP8EncIterator* const it) {
  if (it->lf_stats_ != NULL) {
    int s;
    VP8Encoder* const enc = it->enc_;
    for (s = 0; s < NUM_MB_SEGMENTS; s++) {
      int i, best_level = 0;

      double best_v = 1.00001 * (*it->lf_stats_)[s][0];
      for (i = 1; i < MAX_LF_LEVELS; i++) {
        const double v = (*it->lf_stats_)[s][i];
        if (v > best_v) {
          best_v = v;
          best_level = i;
        }
      }
      enc->dqm_[s].fstrength_ = best_level;
    }
  }
}
