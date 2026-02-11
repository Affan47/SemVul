nrrdSpaceOriginGet(const Nrrd *nrrd,
                   double vector[NRRD_SPACE_DIM_MAX]) {
  unsigned int sdi, ret;

  if (nrrd && vector) {
    for (sdi=0; sdi<nrrd->spaceDim; sdi++) {
      vector[sdi] = nrrd->spaceOrigin[sdi];
    }
    for (sdi=nrrd->spaceDim; sdi<NRRD_SPACE_DIM_MAX; sdi++) {
      vector[sdi] = AIR_NAN;
    }
    ret = nrrd->spaceDim;
  } else {
    ret = 0;
  }
  return ret;
}
