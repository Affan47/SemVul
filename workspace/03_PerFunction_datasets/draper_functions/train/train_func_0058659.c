fmfr_fillC( FMField *obj, float64 val )
{
  int32 il, ir, ic, wr, hr;
  float64 *pr;

  wr = obj->nColFull;
  hr = obj->nRow;
  for (il = 0; il < obj->nLev; il++) {
    pr = obj->val + obj->offset + wr * hr * il;
    for (ir = 0; ir < hr; ir++) {
      for (ic = 0; ic < obj->nCol; ic++) {


	pr[wr*ir+ic] = val;
      }
    }
  }

  return( RET_OK );
}
