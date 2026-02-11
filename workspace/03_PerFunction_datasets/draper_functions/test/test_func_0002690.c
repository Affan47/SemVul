tr_pivot(const saidx_t *ISAd, saidx_t *first, saidx_t *last) {
  saidx_t *middle;
  saidx_t t;

  t = last - first;
  middle = first + t / 2;

  if(t <= 512) {
    if(t <= 32) {
      return tr_median3(ISAd, first, middle, last - 1);
    } else {
      t >>= 2;
      return tr_median5(ISAd, first, first + t, middle, last - 1 - t, last - 1);
    }
  }
  t >>= 3;
  first  = tr_median3(ISAd, first, first + t, first + (t << 1));
  middle = tr_median3(ISAd, middle - t, middle, middle + t);
  last   = tr_median3(ISAd, last - 1 - (t << 1), last - 1 - t, last - 1);
  return tr_median3(ISAd, first, middle, last);
}
