lagrange_facet_normal(v_id,f_id, norm)
vertex_id v_id;
facet_id f_id;
REAL **norm;
{
  vertex_id *v = get_facet_vertices(f_id);
  struct gauss_lag *gl = &gauss_lagrange[web.dimension][web.gauss2D_order];
  MAT2D(sides,MAXCOORD,MAXCOORD);
  MAT2D(vx,MAXVCOUNT,MAXCOORD);
  int ctrl = web.skel[FACET].ctrlpts;
  int i,j,k,kk;

  get_facet_verts(f_id,vx,NULL);
  for ( k = 0 ; k < ctrl ; k++ ) if ( v[k] == v_id ) break;
  if ( k >= ctrl )
     { sprintf(errmsg,
          "Internal error: Can't find vertex %s in facet %s.\n",ELNAME(v_id),
             ELNAME1(f_id));
       kb_error(2210,errmsg,RECOVERABLE);
     }

  for ( j = 0 ; j < SDIM ; j++ ) sides[0][j] = 0.0;
  for ( i = 1 ; i <= web.dimension ; i++ )
    for ( j = 0 ; j < SDIM ; j++ )
      for ( kk = 0, sides[i][j] = 0.0 ; kk < ctrl ; kk++ )
         sides[i][j] += gl->lpolypart[k][i-1][kk]*vx[kk][j];
  if ( inverted(f_id) )
     for ( j = 0 ; j < SDIM ; j++ ) sides[1][j] = -sides[1][j];
  return kernel_basis_rows(sides+1,norm,web.dimension,SDIM);
}
