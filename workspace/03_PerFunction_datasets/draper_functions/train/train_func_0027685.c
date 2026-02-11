init_reader(void)
{
  char *termVal;

  buff[50] = '\0';
  init_flag(buff_flag, MAXLINE);
  buff_pntr = curr_pntr = 0;

  had_tab = 0;
  had_tab_last = 0;
  termVal = (char *) getenv("TERM");
  if (!strcmp("sun", termVal))
    termId = SUN;
  else if (!strcmp("xterm", termVal) || !strncmp("vt", termVal, 2))
    termId = DEC;
  else if (!strcmp("hft", termVal) || !strncmp("aixterm", termVal, 7))
    termId = HFT;
}
