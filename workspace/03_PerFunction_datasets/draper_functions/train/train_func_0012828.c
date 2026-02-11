vg_getElementDiameters( VolumeGeometry *obj, FMField *out,
			      int32 *edges, int32 edges_nRow, int32 edges_nCol,
			      float64 *coorIn, int32 nNod, int32 dim,
			      int32 *conn, int32 nEl, int32 nEP,
			      int32 *elList, int32 elList_nRow,
			      int32 mode )
{
  int32 ii, ie, id, iel, nd;
  float64 val0 = 0.0, val1 = 0.0, vv, aux = 0.0, exponent;

  if ((mode < 0) && (mode > 2)) {
    errput( ErrHead "ERR_Switch\n" );
    return( RET_Fail );
  }


  nd = obj->bfGM->nRow;
  exponent = 1.0 / ((float64) dim);
  for (ii = 0; ii < elList_nRow; ii++) {
    iel = elList[ii];
    FMF_SetCell( out, ii );

    if ((mode == 0) || (mode == 2)) {
      val0 = 0.0;
      for (ie = 0; ie < edges_nRow; ie++) {
	vv = 0.0;
	for (id = 0; id < nd; id++) {
	  aux = coorIn[dim*conn[nEP*iel+edges[2*ie+1]]+id]
	    - coorIn[dim*conn[nEP*iel+edges[2*ie+0]]+id];


	  vv += aux * aux;
	}
	val0 = Max( val0, aux );
	out->val[0] = val0;
      }
    }
    if ((mode == 1) || (mode == 2)) {
      FMF_SetCell( obj->volume, iel );
      val1 = pow( 0.16 * obj->volume->val[0], exponent );
      out->val[0] = val1;
    }
    if (mode == 2) {
      out->val[0] = Max( val0, val1 );
    }
  }
  return( RET_OK );
}
