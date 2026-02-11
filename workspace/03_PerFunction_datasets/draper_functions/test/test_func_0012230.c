vis_event_comp(a,b)
struct vis_event *a, *b;
{ REAL ma,mb;
  if ( a->time < b->time ) return -1;
  if ( a->time > b->time ) return  1;
  if ( a->type < b->type ) return -1;
  if ( a->type > b->type ) return  1;
  ma = (a->e1->m+a->e2->m);
  mb = (b->e1->m+b->e2->m);
  if ( ma < mb ) return -1;
  if ( ma > mb ) return  1;
  if ( a->e1 < b->e1 ) return -1;
  if ( a->e1 > b->e1 ) return  1;
  if ( a->e2 < b->e2 ) return -1;
  if ( a->e2 > b->e2 ) return  1;
  return 0;
}
