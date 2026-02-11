put_hypo_phoneme(WORD_ID *seq, int n, WORD_INFO *winfo)
{
  int i,j;
  WORD_ID w;
  static char buf[MAX_HMMNAME_LEN];

  if (seq != NULL) {
    for (i=0;i<n;i++) {
      if (i > 0) printf(" |");
      w = seq[i];
      for (j=0;j<winfo->wlen[w];j++) {
	center_name(winfo->wseq[w][j]->name, buf);
	myprintf(" %s", buf);
      }
    }
  }
  printf("\n");
}
