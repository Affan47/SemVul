dfa_state_expand(DFA_INFO *dinfo, int needed)
{
  int oldnum, i;
  oldnum = dinfo->maxstatenum;
  dinfo->maxstatenum += DFA_STATESTEP;
  if (dinfo->maxstatenum < needed) dinfo->maxstatenum = needed;
  dinfo->st = (DFA_STATE *)myrealloc(dinfo->st, sizeof(DFA_STATE) * dinfo->maxstatenum);
  for (i=oldnum;i<dinfo->maxstatenum;i++) {
    dinfo->st[i].number = i;
    dinfo->st[i].status = 0;
    dinfo->st[i].arc = NULL;
  }
}
