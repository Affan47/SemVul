hts_plug(httrackp * opt, const char *argv) {

  const char *arg = strchr(argv, ',');

  if (arg != NULL)
    arg++;


  if (arg == NULL)
    arg = "log-wrapper-info";
  hts_log(opt, arg, "* plugging functions");
  CHAIN_FUNCTION(opt, check_html, process_file, (char *) arg);
  CHAIN_FUNCTION(opt, start, start_of_mirror, (char *) arg);
  CHAIN_FUNCTION(opt, end, end_of_mirror, (char *) arg);

  hts_log(opt, arg, "* module successfully plugged");
  return 1;
}
