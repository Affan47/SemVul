next_terms(int stateid, int *termbuf, int *nextstatebuf)
{
  DFA_ARC *arc, *arc2;
  int cate, ns;
  int cnum;

  cnum = 0;
  for (arc = dfa->st[stateid].arc; arc; arc = arc->next) {
    cate = arc->label;
    ns = arc->to_state;
    if (dfa->is_sp[cate]) {
      for (arc2 = dfa->st[ns].arc; arc2; arc2 = arc2->next) {
	termbuf[cnum] = arc2->label;
	nextstatebuf[cnum] = arc2->to_state;
	cnum++;
      }
    } else {
      termbuf[cnum] = cate;
      nextstatebuf[cnum] = ns;
      cnum++;
    }
  }
  return cnum;
}
