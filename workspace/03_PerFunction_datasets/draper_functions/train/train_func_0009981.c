process_file(t_hts_callbackarg * carg, httrackp * opt, char *html,
                        int len, const char *url_address,
                        const char *url_file) {
  char *prevBase;


  if (CALLBACKARG_PREV_FUN(carg, check_html) != NULL) {
    if (!CALLBACKARG_PREV_FUN(carg, check_html)
        (CALLBACKARG_PREV_CARG(carg), opt, html, len, url_address, url_file)) {
      return 0;
    }
  }


  if ((prevBase = strstr(html, "<BASE HREF=\"")) != NULL) {
    prevBase[1] = 'X';
  }

  return 1;
}
