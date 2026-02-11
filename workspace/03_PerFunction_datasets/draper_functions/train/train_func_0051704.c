pullInfoSpecNew(void) {
  pullInfoSpec *ispec;

  ispec = AIR_CAST(pullInfoSpec *, calloc(1, sizeof(pullInfoSpec)));
  if (ispec) {
    ispec->info = pullInfoUnknown;
    ispec->source = pullSourceUnknown;
    ispec->volName = NULL;
    ispec->item = 0;
    ispec->prop = pullPropUnknown;
    ispec->scale = AIR_NAN;
    ispec->zero = AIR_NAN;
    ispec->constraint = AIR_FALSE;
    ispec->volIdx = UINT_MAX;
  }
  return ispec;
}
