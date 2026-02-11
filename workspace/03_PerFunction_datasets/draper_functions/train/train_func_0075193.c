startJuggle(void) {
  set_dpm();
  if (set_ini(1) != 0)
    return;
  xbitset();


  bm1=11-11*dpm/DW;
  time_count=0;
  time_period=0;

  status = ST_JUGGLE;
}
