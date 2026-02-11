q_facet_tension_value(f_info)
struct qinfo *f_info;
{ REAL area;
  int i,j,k;
  REAL diag[MAXCOORD];
  REAL D[MAXCOORD];
  REAL U[MAXCOORD][MAXCOORD];

  if ( web.modeltype == QUADRATIC ) return q_facet_tension_q(f_info);
  if ( web.modeltype == LAGRANGE )
      return lagrange_facet_tension_value(f_info);

  area = 1.0;
  for ( i = 0 ; i < web.dimension ; i++ )
  { for ( j = 0 ; j < SDIM ; j++ ) U[i][j] = f_info->sides[0][i][j];
     for ( j = 0 ; j < i ; j++ )
     { REAL su = SDIM_dot(f_info->sides[0][i],U[j])*D[j];
        for ( k = 0 ; k < SDIM ; k++ ) U[i][k] -= su*U[j][k];
     }
     diag[i] = SDIM_dot(U[i],U[i]);
     if ( diag[i] > 0.0 ) D[i] = 1/diag[i];
     else D[i] = 1.0;
     area *= diag[i];
  }

  if ( area > 0.0 )
     area = sqrt(area)/web.simplex_factorial;
  else area = 0.0;
  if ( METH_INSTANCE(f_info->method)->flags & DEFAULT_INSTANCE )
  { set_facet_area(f_info->id,area);
#ifdef SHARED_MEMORY
     if ( nprocs > 1 )
      proc_total_area[GET_THREAD_ID] += area;
     else
#endif
     binary_tree_add(web.total_area_addends,area);
  }
  if ( METH_INSTANCE(f_info->method)->flags & USE_DENSITY )
      area *= get_facet_density(f_info->id);
  return area;
}
