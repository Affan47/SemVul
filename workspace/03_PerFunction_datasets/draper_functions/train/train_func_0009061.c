get_nbest_uniprob(WCHMM_INFO *wchmm, int n)
{
  LOGPROB *u_p;
  WORD_ID w;
  LOGPROB x;
  WORD_INFO *winfo;
  NGRAM_INFO *ngram;

  winfo = wchmm->winfo;
  ngram = wchmm->ngram;

  if (n < 1) n = 1;
  if (n > winfo->num) n = winfo->num;


  u_p = (LOGPROB *)mymalloc(sizeof(LOGPROB) * winfo->num);
  for(w=0;w<winfo->num;w++) {
    if (ngram) {
      x = uni_prob(ngram, winfo->wton[w])
#ifdef CLASS_NGRAM
	+ winfo->cprob[w]
#endif
	;
    } else {
      x = LOG_ZERO;
    }
    if (wchmm->lmvar == LM_NGRAM_USER) {
      x = (*(wchmm->uni_prob_user))(wchmm->winfo, w, x);
    }
    u_p[w] = x;
  }


  qsort(u_p, winfo->num, sizeof(LOGPROB),
	(int (*)(const void *,const void *))compare_prob);


  x = u_p[n-1];
  free(u_p);
  return(x);
}
