axset_compare(const void *a, const void *b){
  struct axset *p1 = (struct axset*)a;
  struct axset *p2 = (struct axset*)b;
  int c;
  c = p2->nAction - p1->nAction;
  if( c==0 ){
    c = p2->iOrder - p1->iOrder;
  }
  assert( c!=0 || p1==p2 );
  return c;
}
