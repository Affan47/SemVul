quadratic_edge_normal(v_id,e_id,norm)
vertex_id v_id;
edge_id e_id;
REAL **norm;
{
  MAT2D(vx,MAXVCOUNT,MAXCOORD);
  vertex_id *v = get_edge_vertices(e_id);
  int k,m,i;
  int ctrl = web.skel[EDGE].ctrlpts;
  REAL tang[MAXCOORD],*t=tang;

  get_edge_verts(e_id,vx,NULL);
  for ( k = 0 ; k < ctrl ; k++ ) if ( v[k] == v_id ) break;
  if ( k != 0 ) k = 3 - k;


  for ( i = 0 ; i < SDIM ; i++ ) tang[i] = 0.0;
  for ( m = 0 ; m < ctrl ; m++ )
  { REAL prime;
    prime = quad_tang_coeffs[k][m];
    for ( i = 0 ; i < SDIM ; i++ )
    tang[i] += prime*vx[m][i];
  }
  return kernel_basis_rows(&t,norm,1,SDIM);

}
