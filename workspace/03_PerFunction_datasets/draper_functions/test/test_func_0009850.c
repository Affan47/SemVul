make_terminfo(TERM_INFO *tinfo, DFA_INFO *dinfo, WORD_INFO *winfo)
{
  int i,w,t;
  int tnum;


  tnum = tinfo->term_num = dinfo->term_num;

  tinfo->wnum = (int *)mymalloc(sizeof(int) * tnum);

  for(i=0;i<tnum;i++) tinfo->wnum[i]=0;
  for(w=0;w<winfo->num;w++) {
    tinfo->wnum[winfo->wton[w]]++;
  }

  tinfo->tw = (WORD_ID **)mymalloc(sizeof(WORD_ID *) * tnum);
  for(i=0;i<tnum;i++) {
    tinfo->tw[i] = (WORD_ID *)mymalloc(sizeof(WORD_ID) * tinfo->wnum[i]);
  }

  for(i=0;i<tnum;i++) tinfo->wnum[i]=0;
  for(w=0;w<winfo->num;w++) {
    t = winfo->wton[w];
    tinfo->tw[t][tinfo->wnum[t]] = w;
    tinfo->wnum[t]++;
  }

}
