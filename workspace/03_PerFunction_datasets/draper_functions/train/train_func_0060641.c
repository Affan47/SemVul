d_acoustic_alpha( FMField *out, FMField *in,
			VolumeGeometry *vg,
			int32 *conn, int32 nEl, int32 nEP,
			int32 *elList, int32 elList_nRow )
{
  int32 ii, j, iel, dim, nQP, ret = RET_OK;
  FMField *nodval = 0, *aux = 0, *aux2 = 0;

  nQP = vg->bfGM->nLev;
  dim = vg->bfGM->nRow;

  FMF_SetFirst( out );

  fmf_createAlloc( &aux, 1, nQP, dim, 1 );
  fmf_createAlloc( &aux2, 1, 1, dim, 1 );
  fmf_createAlloc( &nodval, 1, 1, nEP, 1 );

  for (ii = 0; ii < elList_nRow; ii++) {
    iel = elList[ii];

    FMF_SetCell( out, ii );
    FMF_SetCell( vg->det, iel );
    FMF_SetCell( vg->bfGM, iel );

    ele_extractNodalValuesNBN( nodval, in, conn + nEP * iel );
    fmf_mulAB_n1( aux, vg->bfGM, nodval );
    fmf_sumLevelsMulF( aux2, aux, vg->det->val );

    for (j = 0; j < (dim-1); j++)
      out->val[j] = aux2->val[j];

    FMF_SetCellNext( out );

    ERR_CheckGo( ret );
  }

 end_label:
  fmf_freeDestroy( &aux );
  fmf_freeDestroy( &aux2 );
  fmf_freeDestroy( &nodval );

  return( ret );
}
