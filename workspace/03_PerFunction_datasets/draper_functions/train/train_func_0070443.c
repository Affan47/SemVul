htsshow_start(t_hts_callbackarg * carg, httrackp * opt) {
  use_show = 0;
  if (opt->verbosedisplay == 2) {
    use_show = 1;
    vt_clear();
  }
  return 1;
}
