gxltln (struct mapprj *mpj) {
float lndif,ltdif,aspect,aspect2,xdif,xlo,xhi,ydif,ylo,yhi;

  if (mpj->lnmn>=mpj->lnmx) return(1);
  if (mpj->ltmn>=mpj->ltmx) return(1);
  if (mpj->xmn>=mpj->xmx) return(1);
  if (mpj->ymn>=mpj->ymx) return(1);

  lndif = mpj->lnmx - mpj->lnmn;
  ltdif = mpj->ltmx - mpj->ltmn;
  aspect = 1.2*ltdif/lndif;
  aspect2 = (mpj->ymx - mpj->ymn) / (mpj->xmx - mpj->xmn);
  if (aspect > aspect2) {
    xdif = (mpj->xmx - mpj->xmn) * aspect2/aspect;
    xlo = ((mpj->xmx - mpj->xmn)/2.0)-(xdif*0.5);
    xhi = ((mpj->xmx - mpj->xmn)/2.0)+(xdif*0.5);
    mpj->axmx = mpj->xmn + xhi;
    mpj->axmn = mpj->xmn + xlo;
    mpj->aymn = mpj->ymn;
    mpj->aymx = mpj->ymx;
  } else {
    ydif = (mpj->ymx - mpj->ymn) * aspect/aspect2;
    ylo = ((mpj->ymx - mpj->ymn)/2.0)-(ydif*0.5);
    yhi = ((mpj->ymx - mpj->ymn)/2.0)+(ydif*0.5);
    mpj->aymx = mpj->ymn + yhi;
    mpj->aymn = mpj->ymn + ylo;
    mpj->axmn = mpj->xmn;
    mpj->axmx = mpj->xmx;
  }

  gxscal (mpj->axmn, mpj->axmx, mpj->aymn, mpj->aymx,
          mpj->lnmn, mpj->lnmx, mpj->ltmn, mpj->ltmx);
  gxproj (NULL);
  adjtyp = 0;
  return (0);
}
