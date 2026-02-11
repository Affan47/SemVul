CreateEigenLocker(Eigen *E,int neigs, int n){
  int info;
  DSDPCALLOC2(&E->eigval,double,neigs,&info);DSDPCHKERR(info);
  DSDPCALLOC2(&E->an,double,n*neigs,&info);DSDPCHKERR(info);
  E->neigs=neigs;
  return 0;
}
