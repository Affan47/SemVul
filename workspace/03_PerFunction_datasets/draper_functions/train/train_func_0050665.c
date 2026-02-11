_tenEpiRegBB(Nrrd *nval, Nrrd *nsize) {
  unsigned char *val;
  int *size, big;
  unsigned int ci;

  val = (unsigned char *)(nval->data);
  size = (int *)(nsize->data);
  big = 0;
  for (ci=0; ci<nsize->axis[0].size; ci++) {
    big = val[ci] ? AIR_MAX(big, size[ci]) : big;
  }
  return big;
}
