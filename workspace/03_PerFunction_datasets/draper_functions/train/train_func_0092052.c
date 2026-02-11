fmf_mulAF( FMField *objR, FMField *objA, float64 *val )
{
  int32 i, il;
  float64 *pr, *pa;

#ifdef DEBUG_FMF
  if ((objR->nRow != objA->nRow) || (objR->nCol != objA->nCol)
      || (objR->nLev != objA->nLev)) {
    errput( ErrHead "ERR_BadMatch\n" );
  }
#endif

  for (il = 0; il < (objR->nLev); il++) {
    pr = objR->val + objR->nCol * objR->nRow * il;
    pa = objA->val + objA->nCol * objA->nRow * il;
    for (i = 0; i < (objR->nRow * objR->nCol); i++) {
      pr[i] = pa[i] * val[il];
    }
  }

  return( RET_OK );
}
