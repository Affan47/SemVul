dw_lin_elastic( FMField *out, float64 coef, FMField *strain,
		      FMField *mtxD, VolumeGeometry *vg,
		      int32 *elList, int32 elList_nRow,
		      int32 isDiff )
{
  int32 ii, iel, dim, sym, nQP, nEP, ret = RET_OK;
  FMField *stress = 0;
  FMField *res = 0, *gtd = 0, *gtdg = 0;

  nQP = vg->bfGM->nLev;
  nEP = vg->bfGM->nCol;
  dim = vg->bfGM->nRow;
  sym = (dim + 1) * dim / 2;


  if (isDiff) {
    fmf_createAlloc( &gtd, 1, nQP, nEP * dim, sym );
    fmf_createAlloc( &gtdg, 1, nQP, nEP * dim, nEP * dim );

    for (ii = 0; ii < elList_nRow; ii++) {
      iel = elList[ii];

      FMF_SetCell( out, ii );
      FMF_SetCell( mtxD, ii );
      FMF_SetCell( vg->bfGM, iel );
      FMF_SetCell( vg->det, iel );

      form_sdcc_actOpGT_M3( gtd, vg->bfGM, mtxD );
      form_sdcc_actOpG_RM3( gtdg, gtd, vg->bfGM );
      fmf_sumLevelsMulF( out, gtdg, vg->det->val );

      ERR_CheckGo( ret );
    }
  } else {
    fmf_createAlloc( &stress, 1, nQP, sym, 1 );
    fmf_createAlloc( &res, 1, nQP, dim * nEP, 1 );

    for (ii = 0; ii < elList_nRow; ii++) {
      iel = elList[ii];

      FMF_SetCell( out, ii );
      FMF_SetCell( mtxD, iel );
      FMF_SetCell( vg->bfGM, iel );
      FMF_SetCell( vg->det, iel );
      FMF_SetCell( strain, iel );

      fmf_mulAB_nn( stress, mtxD, strain );
      form_sdcc_actOpGT_VS3( res, vg->bfGM, stress );
      fmf_sumLevelsMulF( out, res, vg->det->val );
      ERR_CheckGo( ret );
    }
  }


  fmfc_mulC( out, coef );

 end_label:
  if (isDiff) {
    fmf_freeDestroy( &gtd );
    fmf_freeDestroy( &gtdg );
  } else {
    fmf_freeDestroy( &res );
    fmf_freeDestroy( &stress );
  }

  return( ret );
}
