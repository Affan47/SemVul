ml_gd_finalize(value v) {
  if (IM_VAL(v))
    gdImageDestroy(IM_VAL(v));
}
