dotrace(void)
{
  register int  i;
  auto     char s[BUFSIZ];


  print_msg(PRT_NORMAL, ">>>>>>> TRACE (CR=next, q=quit, d=dump, g=go):");
  fgets(s, BUFSIZ, stdin);

  if (*s == 'q')
    exit(0);
  else if (*s == 'g')
    trace = 0;
  else if (*s == 'd') {

    print_msg(PRT_NORMAL, "chan=%d\n", chan);

    for (i = 0; i < MAXCHAN; i++) {
      if (call[i].state) {
        print_msg(PRT_NORMAL, "call[%d]:", i);
        print_msg(PRT_NORMAL, "state=%d, cref=%d, dialin=%d, cause=%d\n",
          call[i].state, call[i].cref, call[i].dialin, call[i].cause);
        print_msg(PRT_NORMAL, "\taoce=%d, channel=%d, dialog=%d, bearer=%d\n",
          call[i].aoce, call[i].channel, call[i].dialog, call[i].bearer);
        print_msg(PRT_NORMAL, "\tnum[0]=\"%s\", num[1]=\"%s\"\n",
          call[i].num[0], call[i].num[1]);
        print_msg(PRT_NORMAL, "\tvnum[0]=\"%s\", vnum[1]=\"%s\"\n",
          call[i].vnum[0], call[i].vnum[1]);
        print_msg(PRT_NORMAL, "\tconfentry[0]=%d,  confentry[1]=%d\n",
          call[i].confentry[0], call[i].confentry[1]);
        print_msg(PRT_NORMAL, "\ttime=%d, connect=%d, disconnect=%d, duration=%d\n",
          (int)call[i].time, (int)call[i].connect, (int)call[i].disconnect, (int)call[i].duration);
      }
    }

    dotrace();

  }
}
