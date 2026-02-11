facet_2form_integral(f_info)
struct qinfo *f_info;
{ int m,i,j,k;
  REAL value=0.0;
  REAL sign = (get_fattr(f_info->id) & NEGBOUNDARY) ? -1.0 : 1.0;

  if ( web.modeltype == LAGRANGE ) return facet_2form_integral_lagrange(f_info);

  for ( m = 0 ; m < gauss2D_num ; m++ )
  {
    f_info->gauss_pt[m][2*SDIM] = m;
    for ( i = 0, k = 0 ; i < SDIM ; i++ )
      for ( j = i+1 ; j < SDIM ; j++,k++ )
      { REAL  form = gauss2Dwt[m]*
           eval(METH_INSTANCE(f_info->method)->expr[k],f_info->gauss_pt[m],f_info->id,NULL);
        value += (f_info->sides[0][0][i]*f_info->sides[0][1][j]
                 - f_info->sides[0][0][j]*f_info->sides[0][1][i])*form;
      }
  }
  return sign*value/2;
}
