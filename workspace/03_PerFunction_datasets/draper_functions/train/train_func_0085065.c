simplex_vertex_normal(v_id,norm)
vertex_id v_id;
REAL **norm;
{ facet_id f_id,startf;
  MAT2D(sides,MAXCOORD,MAXCOORD);
  int i,j;

  if ( SDIM > web.dimension+1 )
  { kb_error(2182,"Can do hessian_normal only for hypersurfaces in simplex model.\n",RECOVERABLE );
  }

  if ( get_vattr(v_id) & TRIPLE_PT )
  { REAL xx[MAXCOORD],val;
    int at = find_attribute(VERTEX,"mirror");
    int connum;
    if ( at < 0 )  return 0;
    connum = *(int*)get_extra(v_id,at);
    for ( i = 0 ; i < SDIM ; i++ ) xx[i] = 0.0;
    eval_all(get_constraint(connum)->formula,xx,SDIM,&val,norm[0],v_id);
  }
  else
  {
    for ( i = 0 ; i < SDIM ; i++ ) norm[0][i] = 0.0;
    startf = f_id = get_vertex_first_facet(v_id);
    do
    { get_facet_verts(f_id,sides,NULL);
      for ( i = 1 ; i <= web.dimension ; i++ )
        for ( j = 0 ; j < SDIM ; j++ )
          sides[i][j] -= sides[0][j];
      det_adjoint(sides,SDIM);
      for ( i = 0 ; i < SDIM ; i++ ) norm[0][i] += sides[i][0];
      f_id = get_next_vertex_facet(v_id,f_id);
    } while ( !equal_element(f_id,startf) );
  }

  return 1;
}
