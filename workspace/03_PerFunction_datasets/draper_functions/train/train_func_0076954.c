uprootTree (tree *tr, nodeptr p)
  {
    nodeptr  q, r, s, start;
    int      n;

    if (p->tip || p->back) {
      printf("ERROR: Unable to uproot tree.\n");
      printf("       Inappropriate node marked for removal.\n");
      return (nodeptr) NULL;
      }

    n = --(tr->nextnode);
    if (n != tr->mxtips + tr->ntips - 1) {
      printf("ERROR: Unable to uproot tree.  Inconsistent\n");
      printf("       number of tips and nodes for rooted tree.\n");
      return (nodeptr) NULL;
      }

    q = p->next->back;
    r = p->next->next->back;
    hookup(q, r, tr->userlen ? (q->z * r->z) : defaultz);

    start = (r->tip || (! q->tip)) ? r : r->next->next->back;

    if (tr->ntips > 2 && p->number != n) {
      q = tr->nodep[n];
      r = q->next;
      s = q->next->next;
      hookup(p,             q->back, q->z);
      hookup(p->next,       r->back, r->z);
      hookup(p->next->next, s->back, s->z);
      if (start->number == q->number) start = start->back->back;
      q->back = r->back = s->back = (nodeptr) NULL;
      }
    else {
      p->back = p->next->back = p->next->next->back = (nodeptr) NULL;
      }

    tr->rooted = FALSE;
    return  start;
  }
