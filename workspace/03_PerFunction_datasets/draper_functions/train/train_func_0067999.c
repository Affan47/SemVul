VP8LGetHistoImageSymbols(int xsize, int ysize,
                             const VP8LBackwardRefs* const refs,
                             int quality, int histo_bits, int cache_bits,
                             VP8LHistogramSet* const histo_image,
                             uint16_t* const histogram_symbols) {
  int ok = 0;
  const int histo_xsize = histo_bits ? VP8LSubSampleSize(xsize, histo_bits) : 1;
  const int histo_ysize = histo_bits ? VP8LSubSampleSize(ysize, histo_bits) : 1;
  const int histo_image_raw_size = histo_xsize * histo_ysize;


  const int bin_depth = histo_image_raw_size + 1;
  int16_t* bin_map = NULL;
  VP8LHistogramSet* const histos = VP8LAllocateHistogramSet(2, cache_bits);
  VP8LHistogramSet* const init_histo =
      VP8LAllocateHistogramSet(histo_image_raw_size, cache_bits);

  if (init_histo == NULL || histos == NULL) {
    goto Error;
  }


  if (init_histo->size > 2 * BIN_SIZE && quality < 90) {
    const int bin_map_size = bin_depth * BIN_SIZE;
    bin_map = (int16_t*)WebPSafeCalloc(bin_map_size, sizeof(*bin_map));
    if (bin_map == NULL) goto Error;
  }


  HistogramBuild(xsize, histo_bits, refs, init_histo);

  if (bin_map != NULL) {
    const double combine_cost_factor =
        GetCombineCostFactor(histo_image_raw_size, quality);
    HistogramAnalyzeBin(init_histo, histo_image, bin_map);
    HistogramCombineBin(histo_image, histos->histograms[0],
                        bin_depth, combine_cost_factor, bin_map);
  } else {
    HistogramAnalyze(init_histo, histo_image);
  }


  HistogramCombine(histo_image, histos, quality);


  HistogramRemap(init_histo, histo_image, histogram_symbols);

  ok = 1;

 Error:
  WebPSafeFree(bin_map);
  VP8LFreeHistogramSet(init_histo);
  VP8LFreeHistogramSet(histos);
  return ok;
}
