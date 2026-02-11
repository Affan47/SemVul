clist_member(Topform c, Clist l)
{
  Clist_pos p;

  for (p = c->containers; p; p = p->nocc) {
    if (p->list == l)
      return TRUE;
  }
  return FALSE;
}
