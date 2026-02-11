form_sdcc_actOpG_RM3( FMField *diff, FMField *mtx, FMField *gc )
{
  int32 iqp, iep, ii, nEP, nQP, nRow;
  float64 *pdiff1, *pdiff2, *pdiff3, *pvec, *pg1, *pg2, *pg3;

  nEP = gc->nCol;
  nQP = gc->nLev;
  nRow = mtx->nRow;

  switch (gc->nRow) {
  case 3:
    for (iqp = 0; iqp < nQP; iqp++) {
      pg1 = FMF_PtrLevel( gc, iqp );
      pg2 = pg1 + nEP;
      pg3 = pg2 + nEP;

      for (ii = 0; ii < nRow; ii++) {
	pvec = FMF_PtrLevel( mtx, iqp ) + mtx->nCol * ii;
	pdiff1 = FMF_PtrLevel( diff, iqp ) + diff->nCol * ii;
	pdiff2 = pdiff1 + nEP;
	pdiff3 = pdiff2 + nEP;
	for (iep = 0; iep < nEP; iep++) {
	  pdiff1[iep]
	    = pg1[iep] * pvec[0]
	    + pg2[iep] * pvec[3]
	    + pg3[iep] * pvec[4];
	  pdiff2[iep]
	    = pg1[iep] * pvec[3]
	    + pg2[iep] * pvec[1]
	    + pg3[iep] * pvec[5];
	  pdiff3[iep]
	    = pg1[iep] * pvec[4]
	    + pg2[iep] * pvec[5]
	    + pg3[iep] * pvec[2];
	}
      }
    }
    break;
  case 2:
    for (iqp = 0; iqp < nQP; iqp++) {
      pg1 = FMF_PtrLevel( gc, iqp );
      pg2 = pg1 + nEP;

      for (ii = 0; ii < nRow; ii++) {
	pvec = FMF_PtrLevel( mtx, iqp ) + mtx->nCol * ii;
	pdiff1 = FMF_PtrLevel( diff, iqp ) + diff->nCol * ii;
	pdiff2 = pdiff1 + nEP;
	for (iep = 0; iep < nEP; iep++) {
	  pdiff1[iep]
	    = pg1[iep] * pvec[0]
	    + pg2[iep] * pvec[2];
	  pdiff2[iep]
	    = pg1[iep] * pvec[2]
	    + pg2[iep] * pvec[1];
	}
      }
    }
    break;
  default:
    errput( ErrHead "ERR_Switch\n" );
  }

  return( RET_OK );
}
