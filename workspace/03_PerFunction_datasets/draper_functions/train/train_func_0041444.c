aaScale() {
  SplashXPathSeg *seg;
  int i;

  for (i = 0, seg = segs; i < length; ++i, ++seg) {
    seg->x0 *= splashAASize;
    seg->y0 *= splashAASize;
    seg->x1 *= splashAASize;
    seg->y1 *= splashAASize;
  }
}
