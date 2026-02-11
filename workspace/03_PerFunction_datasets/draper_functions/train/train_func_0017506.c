_nrrdHestBoundarySpecParse(void *ptr, char *str, char err[AIR_STRLEN_HUGE]) {
  NrrdBoundarySpec **bsp;
  char me[]="_nrrdHestBoundarySpecParse", *nerr;

  if (!(ptr && str)) {
    sprintf(err, "%s: got NULL pointer", me);
    return 1;
  }
  bsp = (NrrdBoundarySpec **)ptr;
  *bsp = nrrdBoundarySpecNew();
  if (nrrdBoundarySpecParse(*bsp, str)) {
    nerr = biffGetDone(NRRD);
    airStrcpy(err, AIR_STRLEN_HUGE, nerr);

    free(nerr);
    return 1;
  }
  return 0;
}
