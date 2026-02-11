edge_vector_integral_grad(e_info)
struct qinfo *e_info;
{ int m,j,k;
  REAL value = 0.0;
  REAL val[MAXCOORD];
  REAL derivs[MAXCOORD][MAXCOORD];
  REAL sum;
  REAL sign = (get_eattr(e_info->id) & NEGBOUNDARY) ? -1.0 : 1.0;

  if ( web.modeltype == QUADRATIC ) return edge_vector_integral_q_grad(e_info);
  if ( web.modeltype == LAGRANGE )
     return edge_vector_integral_lagrange_grad(e_info);
  for ( k = 0 ; k < 2 ; k++ )
     for ( j = 0 ; j < SDIM ; j++ )
        e_info->grad[k][j] = 0.0;
  for ( m = 0 ; m < gauss1D_num ; m++ )
  { REAL weight = sign*gauss1Dwt[m];
    e_info->gauss_pt[m][2*SDIM] = m;
    for ( j = 0 ; j < SDIM ; j++ )
      eval_all(METH_INSTANCE(e_info->method)->expr[j],e_info->gauss_pt[m],SDIM,
        val+j, derivs[j],e_info->id);
    value += gauss1Dwt[m]*SDIM_dot(val,e_info->sides[0][0]);
    for ( k = 0 ; k < SDIM ; k++ )
    { for ( sum = 0.0, j = 0 ; j < SDIM ; j++ )
        sum += derivs[j][k]*e_info->sides[0][0][j];
      e_info->grad[0][k] += weight*(-val[k] + gauss1poly[0][m]*sum);
      e_info->grad[1][k] += weight*(val[k] + gauss1poly[1][m]*sum);
    }
  }

  return sign*value;
}
