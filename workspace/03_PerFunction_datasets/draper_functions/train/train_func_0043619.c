htsshow_query3(t_hts_callbackarg * carg,
                                          httrackp * opt,
                                          const char *question) {
  static char line[256];

  printf("\n" "A link, %s, is located beyond this mirror scope.\n"
         "What should I do? (type in the choice + enter)\n\n"
         "* Ignore all further links and do not ask any more questions\n"
         "0 Ignore this link (default if empty entry)\n"
         "1 Ignore directory and lower structures\n" "2 Ignore all domain\n"
         "\n" "4 Get only this page/link, but not links inside this page\n"
         "5 Mirror this link (useful)\n"
         "6 Mirror all links located on the same domain as this link\n" "\n",
         question);
  do {
    printf(">> ");
    io_flush;
    linput(stdin, line, 200);
  } while(!strnotempty(line));
  printf("ok..\n");
  return line;
}
