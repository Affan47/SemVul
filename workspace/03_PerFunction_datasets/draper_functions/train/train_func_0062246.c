transfer_i_to_C (int i)
{
  int j;
  if (nC > 0) {

    for (j=0; j<nC; j++) L[nC*nskip+j] = ell[j];
    d[nC] = dRecip (AROW(i)[i] - dDot(ell,Dell,nC));
  }
  else {
    d[0] = dRecip (AROW(i)[i]);
  }
  swapProblem (A,x,b,w,lo,hi,p,state,findex,n,nC,i,nskip,1);
  C[nC] = nC;
  nC++;

# ifdef DEBUG_LCP
  checkFactorization (A,L,d,nC,C,nskip);
  if (i < (n-1)) checkPermutations (i+1,n,nC,nN,p,C);
# endif
}
