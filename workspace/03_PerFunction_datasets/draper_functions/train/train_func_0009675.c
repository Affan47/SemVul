facet_general_grad(f_info)
struct qinfo *f_info;
{ int m,j,k;
  REAL value = 0.0;
  REAL val;
  REAL derivs[2*MAXCOORD];
  REAL z[2*MAXCOORD+1];
  REAL sign = (get_fattr(f_info->id) & NEGBOUNDARY) ? -1.0 : 1.0;
  REAL *normal = z+SDIM;

  if ( web.modeltype == LAGRANGE )
     return facet_general_grad_lagr(f_info);

  facet_general_flag = 1;
  for ( m = 0 ; m < gauss2D_num ; m++ )
  {
     REAL coeff = gauss2Dwt[m]/web.simplex_factorial;
     REAL **s = f_info->sides[m];
     z[2*SDIM] = m;
     for ( k = 0 ; k < SDIM ; k++ ) z[k] = f_info->gauss_pt[m][k];
     cross_prod(f_info->sides[m][0],f_info->sides[m][1],normal);
     if ( sign == -1.0 )
        for ( k = 0 ; k < SDIM ; k++ ) z[k+SDIM] *= sign ;
     eval_all(METH_INSTANCE(f_info->method)->expr[0],z,2*SDIM,&val,derivs,f_info->id);
     value += coeff*val;
     for ( j = 0 ; j < 3 ; j++ )
      { int jj = (j+1)%3;
         int jjj = (j+2)%3;
         for ( k = 0 ; k < ctrl_num ; k++ )
         { REAL **gpd = gpolypartial[m];
            f_info->grad[k][j] += coeff*(gpoly[m][k]*derivs[j]
              - sign*derivs[jj+SDIM]*(s[1][jjj]*gpd[0][k]-s[0][jjj]*gpd[1][k])
              - sign*derivs[jjj+SDIM]*(s[0][jj]*gpd[1][k]-s[1][jj]*gpd[0][k]));
         }
      }
  }
  facet_general_flag = 0;
  return value;
}
