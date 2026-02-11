CreateSpRowMatWdata(int m,int n,const double vals[], const int cols[], const int ik[],
			smatx **A){

  smatx *V;

  V=(smatx*) malloc(1*sizeof(smatx));
  if (V==NULL) return 1;
  V->nrow=m;
  V->ncol=n;
  V->owndata=0;
  V->an=vals; V->col=cols; V->nnz=ik;

  *A=V;
  checkvsparse(V);
  return 0;
}
