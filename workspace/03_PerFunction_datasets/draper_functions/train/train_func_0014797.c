fmfc_copyAmulF( FMField *objR, FMField *objA, float64 *val )
{
  int32 i, il, ic;
  float64 *pr, *pa;

#ifdef DEBUG_FMF
  if ((objR->nRow != objA->nRow) || (objR->nCol != objA->nCol)
      || (objR->nLev != objA->nLev) || (objR->nCell != objA->nCell)) {
    errput( ErrHead "ERR_BadMatch\n" );
  }
#endif

  pr = objR->val0;
  pa = objA->val0;
  for (ic = 0; ic < objR->nCell; ic++) {
    for (il = 0; il < (objR->nLev); il++) {
      for (i = 0; i < (objR->nRow * objR->nCol); i++) {
	pr[i] = pa[i] * val[il];
      }
      pr += objR->nCol * objR->nRow;
      pa += objA->nCol * objA->nRow;
    }
    val += objR->nLev;
  }

  return( RET_OK );
}
