dq_tl_finite_strain_surface( FMField *mtxF, FMField *detF, FMField *mtxFI,
				   FMField *state, int32 offset,
				   SurfaceGeometry *sg,
				   int32 *fis, int32 nFa, int32 nFP,
				   int32 *conn, int32 nEl, int32 nEP)
{
  int32 ii, iel, id, iqp, nQP, dim, ret = RET_OK;
  FMField *st = 0;

  state->val = FMF_PtrFirst( state ) + offset;

  nQP = sg->bfBGM->nLev;
  dim = sg->bfBGM->nRow;

  fmf_createAlloc( &st, 1, 1, nEP, dim );

  for (ii = 0; ii < nFa; ii++) {
    iel = fis[ii*nFP+0];

    FMF_SetCell( sg->bfBGM, ii );
    FMF_SetCell( mtxF, ii );
    FMF_SetCell( mtxFI, ii );
    FMF_SetCell( detF, ii );


    ele_extractNodalValuesNBN( st, state, conn + nEP * iel );
    fmf_mulATBT_1n( mtxF, st, sg->bfBGM );
    for (iqp = 0; iqp < nQP; iqp++) {
      for (id = 0; id < dim; id++) {
	mtxF->val[dim*(dim*iqp+id)+id] += 1.0;
      }
    }


    geme_det3x3( detF->val, mtxF );
    for (iqp = 0; iqp < nQP; iqp++) {
      if (detF->val[iqp] <= MachEps) {
	errput( "warp violation %e at (iel: %d, iqp: %d)!\n",
		detF->val[iqp], iel, iqp );
      }
    }
    geme_invert3x3( mtxFI, mtxF );

    ERR_CheckGo( ret );
  }
 end_label:
  fmf_freeDestroy( &st );

  return( ret );
}
