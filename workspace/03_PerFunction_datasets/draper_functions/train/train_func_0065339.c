ddf_MakeLPforInteriorFinding(ddf_LPPtr lp)


{
  ddf_rowrange m;
  ddf_colrange d;
  ddf_NumberType numbtype;
  ddf_LPObjectiveType obj;
  ddf_LPType *lpnew;
  ddf_rowrange i;
  ddf_colrange j;
  myfloat bm,bmax,bceil;
  int localdebug=ddf_FALSE;

  ddf_init(bm); ddf_init(bmax); ddf_init(bceil);
  ddf_add(bm,ddf_one,ddf_one); ddf_set(bmax,ddf_one);
  numbtype=lp->numbtype;
  m=lp->m+1;
  d=lp->d+1;
  obj=ddf_LPmax;

  lpnew=ddf_CreateLPData(obj, numbtype, m, d);

  for (i=1; i<=lp->m; i++) {
    if (ddf_Larger(lp->A[i-1][lp->rhscol-1],bmax))
      ddf_set(bmax,lp->A[i-1][lp->rhscol-1]);
  }
  ddf_mul(bceil,bm,bmax);
  if (localdebug) {fprintf(stderr,"bceil is set to "); ddf_WriteNumber(stderr, bceil);}

  for (i=1; i <= lp->m; i++) {
    for (j=1; j <= lp->d; j++) {
      ddf_set(lpnew->A[i-1][j-1],lp->A[i-1][j-1]);
    }
  }

  for (i=1;i<=lp->m; i++){
    ddf_neg(lpnew->A[i-1][lp->d],ddf_one);
  }

  for (j=1;j<=lp->d;j++){
    ddf_set(lpnew->A[m-2][j-1],ddf_purezero);
  }
  ddf_set(lpnew->A[m-2][0],bceil);

  for (j=1;j<= d-1;j++) {
    ddf_set(lpnew->A[m-1][j-1],ddf_purezero);
  }
  ddf_set(lpnew->A[m-1][d-1],ddf_one);

  if (localdebug) ddf_WriteAmatrix(stderr, lp->A, lp->m, lp->d);
  if (localdebug) ddf_WriteAmatrix(stderr, lpnew->A, lpnew->m, lpnew->d);
  ddf_clear(bm); ddf_clear(bmax); ddf_clear(bceil);

  return lpnew;
}
