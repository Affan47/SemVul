ParsetreeCompare(Parsetree_t *t1, Parsetree_t *t2)
{
  int x;

  if (t1->n != t2->n) return 0;
  for (x = 0; x < t1->n; x++)
    {
      if (t1->emitl[x] != t2->emitl[x]) return 0;
      if (t1->emitr[x] != t2->emitr[x]) return 0;
      if (t1->state[x] != t2->state[x]) return 0;
      if (t1->mode[x]  != t2->mode[x])  return 0;
      if (t1->nxtl[x]  != t2->nxtl[x])  return 0;
      if (t1->nxtr[x]  != t2->nxtr[x])  return 0;
    }
  return 1;
}
