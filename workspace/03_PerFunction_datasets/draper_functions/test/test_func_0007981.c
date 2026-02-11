HistogramRemap(const VP8LHistogramSet* const init_histo,
                           const VP8LHistogramSet* const histo_image,
                           uint16_t* const symbols) {
  int i;
  for (i = 0; i < init_histo->size; ++i) {
    int best_out = 0;
    double best_bits = HistogramAddThresh(histo_image->histograms[0],
                                          init_histo->histograms[i], MAX_COST);
    int k;
    for (k = 1; k < histo_image->size; ++k) {
      const double cur_bits = HistogramAddThresh(histo_image->histograms[k],
                                                 init_histo->histograms[i],
                                                 best_bits);
      if (cur_bits < best_bits) {
        best_bits = cur_bits;
        best_out = k;
      }
    }
    symbols[i] = best_out;
  }


  for (i = 0; i < histo_image->size; ++i) {
    HistogramClear(histo_image->histograms[i]);
  }

  for (i = 0; i < init_histo->size; ++i) {
    VP8LHistogramAdd(init_histo->histograms[i],
                     histo_image->histograms[symbols[i]],
                     histo_image->histograms[symbols[i]]);
  }
}
