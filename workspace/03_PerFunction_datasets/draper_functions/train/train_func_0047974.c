assemble_matrix_complex( FMField *mtx_r, FMField *mtx_i,
			       int32 *prows, int32 prows_len,
			       int32 *cols, int32 cols_len,
			       FMField *mtxInEls_r, FMField *mtxInEls_i,
			       int32 *iels, int32 iels_len,
			       float64 sign_r, float64 sign_i,
			       int32 *connR, int32 nElR, int32 nEPR,
			       int32 *connC, int32 nElC, int32 nEPC )
{
  int32 ii, iel, ir, ic, irg, icg, is, iloc, found, stride, stride2;
  int32 *pconnR, *pconnC;
  float64 *val_r, *val_i;

  stride = mtx_r->stride;
  stride2 = mtxInEls_r->stride;

  val_r = FMF_PtrFirst( mtx_r );
  val_i = FMF_PtrFirst( mtx_i );

  for (ii = 0; ii < iels_len; ii++) {
    iel = iels[ii];
    FMF_SetCell( mtxInEls_r, ii );
    FMF_SetCell( mtxInEls_i, ii );

    pconnR = connR + nEPR * iel;
    pconnC = connC + nEPC * iel;

    for (ir = 0; ir < nEPR; ir++) {
      irg = pconnR[ir];
      if (irg < 0) continue;

      for (ic = 0; ic < nEPC; ic++) {
	icg = pconnC[ic];
	if (icg < 0) continue;
	iloc = stride2 * (nEPC * ir + ic);


	found = 0;
	for (is = prows[irg]; is < prows[irg+1]; is++) {
	  if (cols[is] == icg) {
	    val_r[stride*is] += sign_r * mtxInEls_r->val[iloc]
	      - sign_i * mtxInEls_i->val[iloc];
	    val_i[stride*is] += sign_r * mtxInEls_i->val[iloc]
	      + sign_i * mtxInEls_r->val[iloc];
	    found = 1;
	    break;
	  }
	}
	if (!found) {
	  errput( "matrix item (%d,%d) does not exist\n", irg, icg );
	  return( RET_Fail );
	}
      }
    }


  }


  return( RET_OK );
}
