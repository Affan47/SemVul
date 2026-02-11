fmf_mulAB_n1( FMField *objR, FMField *objA, FMField *objB )
{
  int32 i, j, k, il, wr, wa, wb;
  float64 *pr, *pa, *pb;

#ifdef DEBUG_FMF
  if ((objR->nRow != objA->nRow) || (objR->nCol != objB->nCol)
      || (objA->nCol != objB->nRow) || (objR->nLev != objA->nLev)
      || (objB->nLev != 1) ) {
    errput( ErrHead "ERR_BadMatch: (%d %d %d) = (%d %d %d) * (%d(1) %d %d)\n",
	    objR->nLev, objR->nRow, objR->nCol,
	    objA->nLev, objA->nRow, objA->nCol,
	    objB->nLev, objB->nRow, objB->nCol );
  }
#endif

  wr = objR->nCol;
  wa = objA->nCol;
  wb = objB->nCol;
  pb = objB->val;
  for (il = 0; il < objR->nLev; il++) {
    pr = objR->val + objR->nCol * objR->nRow * il;
    pa = objA->val + objA->nCol * objA->nRow * il;
    for (i = 0; i < objR->nRow; i++) {
      for (j = 0; j < objR->nCol; j++) {
	pr[wr*i+j] = 0.0;
	for (k = 0; k < objA->nCol; k++) {
	  pr[wr*i+j] += pa[wa*i+k] * pb[wb*k+j];
	}
      }
    }
  }
  return( RET_OK );
}
