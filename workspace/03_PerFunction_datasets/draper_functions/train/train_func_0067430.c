c_ekkftju_sparse_a(COIN_REGISTER2 const EKKfactinfo * COIN_RESTRICT2 fact,
			    int * COIN_RESTRICT mpt,
			    int nincol,int * COIN_RESTRICT spare)
{
  const int * COIN_RESTRICT hrowi	= fact->xeradr+1;
  const int * COIN_RESTRICT mcstrt	= fact->xcsadr;
  const int nrow		= fact->nrow;
  char * COIN_RESTRICT nonzero=fact->nonzero;

  int k,nStack,kx,nel;
  int nList=0;
  int iPivot;

  int * COIN_RESTRICT list = spare;
  int * COIN_RESTRICT stack = spare+nrow;
  int * COIN_RESTRICT next = stack+nrow;
  for (k=0;k<nincol;k++) {
    nStack=1;
    iPivot=mpt[k];
    stack[0]=iPivot;
    next[0]=0;
    while (nStack) {
      int kPivot,j;

      kPivot=stack[--nStack];
      if (nonzero[kPivot]!=1) {
	kx = mcstrt[kPivot];
	nel = hrowi[kx-1];
	j=next[nStack];
	if (j==nel) {

	  list[nList++]=kPivot;
	  nonzero[kPivot]=1;
	} else {
	  kPivot=hrowi[kx+j];

	  next[nStack++] ++;
	  if (!nonzero[kPivot]) {

	    stack[nStack]=kPivot;
	    nonzero[kPivot]=2;
	    next[nStack++]=0;

	  }
	}
      }
    }
  }
  return (nList);
}
