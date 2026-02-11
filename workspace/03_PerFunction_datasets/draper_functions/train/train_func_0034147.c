actioncmp(ap1,ap2)
struct action *ap1;
struct action *ap2;
{
  int rc;
  rc = ap1->sp->index - ap2->sp->index;
  if( rc==0 ) rc = (int)ap1->type - (int)ap2->type;
  if( rc==0 ){
    assert( ap1->type==REDUCE && ap2->type==REDUCE );
    rc = ap1->x.rp->index - ap2->x.rp->index;
  }
  return rc;
}
