_pullHestEnergyParse(void *ptr, char *str, char err[AIR_STRLEN_HUGE]) {
  static const char me[]="_pullHestForceParse";
  pullEnergySpec **enspP;
  char *perr;

  if (!(ptr && str)) {
    sprintf(err, "%s: got NULL pointer", me);
    return 1;
  }
  enspP = (pullEnergySpec **)ptr;
  *enspP = pullEnergySpecNew();
  if (pullEnergySpecParse(*enspP, str)) {
    perr = biffGetDone(PULL);
    airStrcpy(err, AIR_STRLEN_HUGE, perr);
    free(perr);
    return 1;
  }
  return 0;
}
