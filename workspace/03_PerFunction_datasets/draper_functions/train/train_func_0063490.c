HistogramAddEval(const VP8LHistogram* const a,
                               const VP8LHistogram* const b,
                               VP8LHistogram* const out,
                               double cost_threshold) {
  double cost = 0;
  const double sum_cost = a->bit_cost_ + b->bit_cost_;
  cost_threshold += sum_cost;

  if (GetCombinedHistogramEntropy(a, b, cost_threshold, &cost)) {
    VP8LHistogramAdd(a, b, out);
    out->bit_cost_ = cost;
    out->palette_code_bits_ = a->palette_code_bits_;
    out->trivial_symbol_ = (a->trivial_symbol_ == b->trivial_symbol_) ?
        a->trivial_symbol_ : VP8L_NON_TRIVIAL_SYM;
  }

  return cost - sum_cost;
}
