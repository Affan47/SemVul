nrrdInit(Nrrd *nrrd) {
  int ii;

  if (nrrd) {
    nrrdBasicInfoInit(nrrd, NRRD_BASIC_INFO_NONE);
    for (ii=0; ii<NRRD_DIM_MAX; ii++) {
      _nrrdAxisInfoInit(nrrd->axis + ii);
    }
  }
  return;
}
