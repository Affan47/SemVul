edge_scalar_integral_lagr(e_info)
struct qinfo *e_info;
{ int m;
  REAL value = 0.0;
  struct gauss_lag *gl = &gauss_lagrange[1][web.gauss1D_order];

  for ( m = 0 ; m < gl->gnumpts ; m++ )
  { e_info->gauss_pt[m][2*SDIM] = m;
    value += gl->gausswt[m]
         *eval(METH_INSTANCE(e_info->method)->expr[0],e_info->gauss_pt[m],e_info->id,NULL)
         *sqrt(SDIM_dot(e_info->sides[m][0],e_info->sides[m][0]));
  }
  return value;
}
