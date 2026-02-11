sg_integrate( SurfaceGeometry *obj, FMField *out, FMField *in )
{
  int32 dim, nQP, iel, ret = RET_OK;
  FMField *vn = 0;

  dim = obj->normal->nRow;
  nQP = obj->normal->nLev;

  if (in->nRow == 1) {
    for (iel = 0; iel < obj->det->nCell; iel++) {
      FMF_SetCell( obj->det, iel );
      FMF_SetCell( in, iel );
      FMF_SetCell( out, iel );

      fmf_sumLevelsMulF( out, in, obj->det->val );
      ERR_CheckGo( ret );
    }
  } else if (in->nRow == dim) {
    fmf_createAlloc( &vn, 1, nQP, 1, 1 );

    for (iel = 0; iel < obj->det->nCell; iel++) {
      FMF_SetCell( obj->normal, iel );
      FMF_SetCell( obj->det, iel );
      FMF_SetCell( in, iel );
      FMF_SetCell( out, iel );

      fmf_mulATB_nn( vn, in, obj->normal );


      fmf_sumLevelsMulF( out, vn, obj->det->val );
      ERR_CheckGo( ret );
    }
  } else {
    errput( ErrHead "ERR_Switch\n" );
  }

 end_label:
  fmf_freeDestroy( &vn );

  return( RET_OK );
}
