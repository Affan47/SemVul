ele_extractNodalValuesDBD( FMField *out, FMField *in,
				 int32 *conn )
{
  int32 inod, idof;

  for (idof = 0; idof < out->nRow; idof++ ) {
    for (inod = 0; inod < out->nCol; inod++) {
      out->val[out->nCol*idof+inod] = in->val[out->nRow*conn[inod]+idof];
    }
  }

  return( RET_OK );
}
