BConeCopyX(BCone bcone,double xl[], double xu[], int m){
  int i,ii,*ib,nn;
  double *xx,*au;
  DSDPFunctionBegin;
  BConeValid(bcone);
  if (m!=bcone->m){ DSDPSETERR1(6,"Invalid Array Length.\n",bcone->m);}
  xx=bcone->ux; au=bcone->au; nn=bcone->nn; ib=bcone->ib;
  for (i=0;i<m;i++){
    xl[i]=0;xu[i]=0;
  }
  for (i=0;i<nn;i++){
    ii=ib[i]-1;
    if (au[i]<0){
      xl[ii]+=xx[i];
    } else {
      xu[ii]+=xx[i];
    }
  }
  DSDPFunctionReturn(0);
}
