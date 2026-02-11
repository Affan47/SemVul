meetHestPullVolParse(void *ptr, char *str, char err[AIR_STRLEN_HUGE]) {
  static const char me[]="meetHestPullVolParse";
  meetPullVol *mpv, **mpvP;
  airArray *mop;

  if (!(ptr && str)) {
    sprintf(err, "%s: got NULL pointer", me);
    return 1;
  }
  mop = airMopNew();
  mpvP = AIR_CAST(meetPullVol **, ptr);
  *mpvP = mpv = meetPullVolNew();
  airMopAdd(mop, mpvP, (airMopper)airSetNull, airMopOnError);
  airMopAdd(mop, mpv, (airMopper)meetPullVolNix, airMopOnError);
  if (meetPullVolParse(mpv, str)) {
    char *ler;
    airMopAdd(mop, ler = biffGetDone(MEET), airFree, airMopOnError);
    airStrcpy(err, AIR_STRLEN_HUGE, ler);
    airMopError(mop);
    return 1;
  }
  airMopOkay(mop);
  return 0;
}
