ddf_CreateLP_V_Redundancy(ddf_MatrixPtr M, ddf_rowrange itest)
{
  ddf_rowrange m, i, irev, linc;
  ddf_colrange d, j;
  ddf_LPPtr lp;
  ddf_boolean localdebug=ddf_FALSE;

  linc=set_card(M->linset);
  m=M->rowsize+1+linc;


  d=(M->colsize)+1;


  lp=ddf_CreateLPData(M->objective, M->numbtype, m, d);
  lp->Homogeneous = ddf_FALSE;
  lp->objective = ddf_LPmin;
  lp->eqnumber=linc;
  lp->redcheck_extensive=ddf_FALSE;

  irev=M->rowsize;
  for (i = 1; i <= M->rowsize; i++) {
    if (i==itest){
      ddf_set(lp->A[i-1][0],ddf_one);
    } else {
      ddf_set(lp->A[i-1][0],ddf_purezero);
    }
    if (set_member(i, M->linset)) {
      irev=irev+1;
      set_addelem(lp->equalityset,i);

      for (j = 2; j <= (M->colsize)+1; j++) {
        ddf_neg(lp->A[irev-1][j-1],M->matrix[i-1][j-2]);
      }
      if (localdebug) fprintf(stderr,"equality row %ld generates the reverse row %ld.\n",i,irev);
    }
    for (j = 2; j <= (M->colsize)+1; j++) {
      ddf_set(lp->A[i-1][j-1],M->matrix[i-1][j-2]);
    }
  }
  for (j = 2; j <= (M->colsize)+1; j++) {
    ddf_set(lp->A[m-1][j-1],M->matrix[itest-1][j-2]);

  }
  ddf_set(lp->A[m-1][0],ddf_purezero);

  if (localdebug) ddf_WriteLP(stdout, lp);

  return lp;
}
