mossImageAlloc (Nrrd *image, int type, int sx, int sy, int ncol) {
  static const char me[]="mossImageAlloc";
  int ret;

  if (!(image && AIR_IN_OP(nrrdTypeUnknown, type, nrrdTypeBlock)
        && sx > 0 && sy > 0 && ncol > 0)) {
    biffAddf(MOSS, "%s: got NULL pointer or bad args", me);
    return 1;
  }
  if (1 == ncol) {
    ret = nrrdMaybeAlloc_va(image, type, 2,
                            AIR_CAST(size_t, sx),
                            AIR_CAST(size_t, sy));
  } else {
    ret = nrrdMaybeAlloc_va(image, type, 3,
                            AIR_CAST(size_t, ncol),
                            AIR_CAST(size_t, sx),
                            AIR_CAST(size_t, sy));
  }
  if (ret) {
    biffMovef(MOSS, NRRD, "%s: couldn't allocate image", me);
    return 1;
  }


  return 0;
}
