_nrrdMeasureCoV(void *ans, int ansType,
                const void *line, int lineType, size_t len,
                double axmin, double axmax) {
  double val, S, M, (*lup)(const void*, size_t), diff, stdv;
  size_t ii, count;

  AIR_UNUSED(axmin);
  AIR_UNUSED(axmax);
  lup = nrrdDLookup[lineType];
  if (nrrdTypeIsIntegral[lineType]) {
    S = 0.0;
    for (ii=0; ii<len; ii++) {
      S += lup(line, ii);
    }
    M = S/len;
    diff = 0.0;
    for (ii=0; ii<len; ii++) {
      val = lup(line, ii);
      diff += (M-val)*(M-val);
    }
    stdv = sqrt(diff/len);
  } else {
    S = AIR_NAN;
    for (ii=0; !AIR_EXISTS(S) && ii<len; ii++) {
      S = lup(line, ii);
    }
    if (AIR_EXISTS(S)) {

      count = 1;
      for (; ii<len; ii++) {
        val = lup(line, ii);
        if (AIR_EXISTS(val)) {
          count++;
          S += val;
        }
      }
      M = S/count;
      diff = 0.0;
      for (ii=0; ii<len; ii++) {
        val = lup(line, ii);
        if (AIR_EXISTS(val)) {
          diff += (M-val)*(M-val);
        }
      }
      stdv = sqrt(diff/count);
    } else {

      M = stdv = AIR_NAN;
    }
  }
  nrrdDStore[ansType](ans, stdv/M);
}
