VechMatGetEig(void* AA, int rank, double *eigenvalue, double vv[], int n, int indx[], int *nind){
  vechmat*  A=(vechmat*)AA;
  const double *val=A->val,tt=sqrt(0.5);
  int info,i,j,k,t;
  const int *ind=A->ind,ishift=A->ishift;

  *nind=0;
  switch (A->factored){
  case 1:
    memset(vv,0,n*sizeof(double));
    t=ind[rank]-ishift;
    i=GETI(t,n);
    j=GETJ(t,n);
    vv[i]=1.0;
    *eigenvalue=val[rank]*A->alpha;
    *nind=1;
    indx[0]=i;
    break;
  case 2:
    memset(vv,0,n*sizeof(double));
    k=rank/2;
    getij(ind[k]-ishift,n,&i,&j);
    if (i==j){
      if (k*2==rank){
	vv[i]=1.0; *eigenvalue=val[k]*A->alpha;
	*nind=1;
	indx[0]=i;
      } else {
	*eigenvalue=0;
      }
    } else {
      if (k*2==rank){
	vv[i]=tt;  vv[j]=tt; *eigenvalue=val[k]*A->alpha;
	*nind=2;
	indx[0]=i; indx[1]=j;
      } else {
	vv[i]=-tt; vv[j]=tt; *eigenvalue=-val[k]*A->alpha;
	*nind=2;
	indx[0]=i; indx[1]=j;
      }
    }
    break;
  case 3:
    info=EigMatGetEig(A->Eig,rank,eigenvalue,vv,n,indx,nind);DSDPCHKERR(info);
    *eigenvalue=*eigenvalue*A->alpha;
    break;
  default:
    DSDPSETERR(1,"Vech Matrix not factored yet\n");
  }

  return 0;
}
