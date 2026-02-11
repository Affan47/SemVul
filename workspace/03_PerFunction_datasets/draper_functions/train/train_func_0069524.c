fmf_addAmulF( FMField *objR, FMField *objA, float64 *val )
{
  int32 ii, il;
  float64 *pr, *pa;

#ifdef DEBUG_FMF
  if ((objR->nRow != objA->nRow) || (objR->nCol != objA->nCol)
      || (objR->nLev != objA->nLev)) {
    errput( ErrHead "ERR_BadMatch: (%d %d %d) = (%d %d %d) * C\n",
	    objR->nLev, objR->nRow, objR->nCol,
	    objA->nLev, objA->nRow, objA->nCol );
  }
#endif

  pr = objR->val;
  pa = objA->val;
  for (il = 0; il < (objR->nLev); il++) {
    for (ii = 0; ii < (objR->nRow * objR->nCol); ii++) {
      pr[ii] += pa[ii] * val[il];
    }
    pr += objR->nCol * objR->nRow;
    pa += objA->nCol * objA->nRow;
  }

  return( RET_OK );
}
