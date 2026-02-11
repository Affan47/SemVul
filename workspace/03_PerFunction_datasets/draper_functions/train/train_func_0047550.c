go_offline_with_marker(const char *mrk) {
  UBool wasON_LINE = ON_LINE;

  if(ON_LINE) {
    log_testinfo(" {\n");
    ON_LINE=FALSE;
  }

  if(!HANGING_OUTPUT || wasON_LINE) {
    if(mrk != NULL) {
      fputs(mrk, stdout);
    }
  }
}
