DSDPVecWAXPBY(DSDPVec w, double alpha,  DSDPVec x,  double beta, DSDPVec y){

  int i,ii,n=x.dim;
  double *yy=y.val,*xx=x.val,*ww=w.val;
  DSPPVecCheck(x,y);
  DSPPVecCheck(x,w);

  for (ii=0; ii<n/4; ++ii){
    i=ii*4;
    ww[i] = (alpha)*xx[i] + (beta)*yy[i];
    ww[i+1] = (alpha)*xx[i+1] + (beta)*yy[i+1];
    ww[i+2] = (alpha)*xx[i+2] + (beta)*yy[i+2];
    ww[i+3] = (alpha)*xx[i+3] + (beta)*yy[i+3];
  }
  for (i=4*(n/4); i<n; ++i){
    ww[i] = (alpha)*xx[i] + (beta)*yy[i];
  }

  return 0;
}
