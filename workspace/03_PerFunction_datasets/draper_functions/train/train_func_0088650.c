put_hypo_wname(WORD_ID *seq, int n, WORD_INFO *winfo)
{
  int i;

  if (seq != NULL) {
    for (i=0;i<n;i++) {
      myprintf(" %s",winfo->wname[seq[i]]);
    }
  }
  printf("\n");
}
