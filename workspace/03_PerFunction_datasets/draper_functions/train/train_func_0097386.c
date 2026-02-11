_tenEpiRegPairXforms(Nrrd *npxfr, Nrrd **nmom, int ninLen) {
  static const char me[]="_tenEpiRegPairXforms";
  double *xfr, *A, *B, hh, ss, tt;
  int ai, bi, zi, sz;

  sz = nmom[0]->axis[1].size;
  if (nrrdMaybeAlloc_va(npxfr, nrrdTypeDouble, 4,
                        AIR_CAST(size_t, 5),
                        AIR_CAST(size_t, sz),
                        AIR_CAST(size_t, ninLen),
                        AIR_CAST(size_t, ninLen))) {
    biffMovef(TEN, NRRD, "%s: couldn't allocate transform nrrd", me);
    return 1;
  }
  nrrdAxisInfoSet_va(npxfr, nrrdAxisInfoLabel,
                     "mx,my,h,s,t", "zi", "orig", "target");
  xfr = (double *)(npxfr->data);
  for (bi=0; bi<ninLen; bi++) {
    for (ai=0; ai<ninLen; ai++) {
      for (zi=0; zi<sz; zi++) {
        A = (double*)(nmom[ai]->data) + 5*zi;
        B = (double*)(nmom[bi]->data) + 5*zi;
        ss = sqrt((A[M_20]*B[M_02] - B[M_11]*B[M_11]) /
                  (A[M_20]*A[M_02] - A[M_11]*A[M_11]));
        hh = (B[M_11] - ss*A[M_11])/A[M_20];
        tt = B[MEAN_Y] - A[MEAN_Y];
        ELL_5V_SET(xfr + 5*(zi + sz*(ai + ninLen*bi)),
                   A[MEAN_X], A[MEAN_Y], hh, ss, tt);
      }
    }
  }
  return 0;
}
