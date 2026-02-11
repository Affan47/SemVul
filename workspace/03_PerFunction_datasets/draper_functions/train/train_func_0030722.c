legal_P3_reduction(EDGE *e)


{
  EDGE *run, *last;
  int v1,v2;

  if (degree[e->next->end]!=3) return 0;
  run=e->invers->prev;
  if (degree[run->end]!=3) return 0;
  run=run->prev->invers->prev;
  if (degree[run->end]!=3) return 0;
  v1=run->start;
   run=run->prev->invers->prev;
  if (degree[run->end]!=3) return 0;
  v2=run->start;


  last=e->prev;
  run=e->next->next->next;
  while (run!=last)
    { if (run->invers->prev->end==v1) return 0;
    run=run->next; }

  e=e->invers;
  last=e->prev->prev->prev;
  run=e->next;
  while (run!=last)
    { if (run->invers->prev->end==v2) return 0;
    run=run->next; }

  return 1;
}
