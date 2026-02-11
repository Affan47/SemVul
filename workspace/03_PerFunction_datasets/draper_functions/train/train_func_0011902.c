badchar(char ** wlst, const char * word, int ns, int cpdsuggest)
{
  char  tmpc;
  char  candidate[MAXSWUTF8L];
  clock_t timelimit = clock();
  int timer = MINTIMER;
  int wl = strlen(word);
  strcpy(candidate, word);


  for (int j=0; j < ctryl; j++) {
    for (int i=wl-1; i >= 0; i--) {
       tmpc = candidate[i];
       if (ctry[j] == tmpc) continue;
       candidate[i] = ctry[j];
       ns = testsug(wlst, candidate, wl, ns, cpdsuggest, &timer, &timelimit);
       if (ns == -1) return -1;
       if (!timer) return ns;
       candidate[i] = tmpc;
    }
  }
  return ns;
}
