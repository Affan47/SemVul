nrrdSpaceVecSetNaN(double vec[NRRD_SPACE_DIM_MAX]) {
  unsigned int di;

  for (di=0; di<NRRD_SPACE_DIM_MAX; di++) {
    vec[di] = AIR_NAN;
  }
  return;
}
