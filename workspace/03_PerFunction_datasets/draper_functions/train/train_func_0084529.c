dfa_nextwords(NODE *hypo, NEXTWORD **nw, int maxnw, RecogProcess *r)
{
  DFA_INFO *dfa;
  DFA_ARC *arc, *arc2;
  int iw,cate,ns,cate2,ns2;
  int num = 0;

  dfa = r->lm->dfa;


  for (arc = dfa->st[hypo->state].arc; arc; arc = arc->next) {
    cate = arc->label;
    ns = arc->to_state;
    if (dfa->is_sp[cate]) {

      for (arc2 = dfa->st[ns].arc; arc2; arc2 = arc2->next) {
	cate2 = arc2->label;
	ns2 = arc2->to_state;
	for (iw=0;iw<dfa->term.wnum[cate2];iw++) {
	  nw[num]->id = dfa->term.tw[cate2][iw];
	  nw[num]->next_state = ns2;
	  nw[num]->can_insert_sp = TRUE;
	  nw[num]->lscore = r->config->lmp.penalty2;
#ifdef CLASS_NGRAM

	  nw[num]->lscore += r->wchmm->winfo->cprob[nw[num]->id];
#endif
	  num++;
	  if (num >= maxnw) return -1;
	}
      }
    } else {

      for (iw=0;iw<dfa->term.wnum[cate];iw++) {
	nw[num]->id = dfa->term.tw[cate][iw];
	nw[num]->next_state = ns;
	nw[num]->can_insert_sp = FALSE;
	nw[num]->lscore = r->config->lmp.penalty2;
#ifdef CLASS_NGRAM

	nw[num]->lscore += r->wchmm->winfo->cprob[nw[num]->id];
#endif
	num++;
	if (num >= maxnw) return -1;
      }
    }
  }
  return num;
}
