put_nextword()
{
  STATECHAIN *tmp;
  int state;
  int *nterms, *nstate;
  int cnum;
  int i,j;
#define NW_PUT_LIMIT 3

  nterms = (int *)mymalloc(sizeof(int)*dfa->term_num * 2);
  nstate = (int *)mymalloc(sizeof(int)*dfa->term_num * 2);

  for(tmp=reach_state; tmp; tmp=tmp->next) {
    state = tmp->state;
    cnum = next_terms(state, nterms, nstate);
    cnum = compaction_int(nterms, cnum);
    for (i=0;i<cnum;i++){
      if (no_term_file) {
	printf("\t%-16d (", nterms[i]);
      } else {
	printf("\t%16s (", termname[nterms[i]]);
      }
      if (dfa->term.wnum[nterms[i]] > NW_PUT_LIMIT) {
	for(j=0;j < NW_PUT_LIMIT;j++) {
	  printf("%s ",winfo->woutput[dfa->term.tw[nterms[i]][j]]);
	}
	printf("...)\n");
      } else {
	for(j=0;j<dfa->term.wnum[nterms[i]];j++) {
	  printf("%s ",winfo->woutput[dfa->term.tw[nterms[i]][j]]);
	}
	printf(")\n");
      }
    }
  }
  free(nterms); free(nstate);
}
