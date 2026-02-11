dfa_nextwords(NODE *hypo, NEXTWORD **nw)
{
  DFA_ARC *arc, *arc2;
  int iw,cate,ns,cate2,ns2;
  int num = 0;

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
	  num++;
	}
      }
    } else {

      for (iw=0;iw<dfa->term.wnum[cate];iw++) {
	nw[num]->id = dfa->term.tw[cate][iw];
	nw[num]->next_state = ns;
	nw[num]->can_insert_sp = FALSE;
	num++;
      }
    }
  }
  return num;
}
