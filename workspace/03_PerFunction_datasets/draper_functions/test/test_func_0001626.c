VP8SSIMGetSquaredError(const DistoStats* const s) {
  if (s->w > 0.) {
    const double iw2 = 1. / (s->w * s->w);
    const double sxx = s->xxm * s->w - s->xm * s->xm;
    const double syy = s->yym * s->w - s->ym * s->ym;
    const double sxy = s->xym * s->w - s->xm * s->ym;
    const double SSE = iw2 * (sxx + syy - 2. * sxy);
    if (SSE > kMinValue) return SSE;
  }
  return kMinValue;
}
