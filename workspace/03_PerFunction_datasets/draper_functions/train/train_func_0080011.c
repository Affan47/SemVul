facet_scalar_integral_q_grad(f_info)
struct qinfo *f_info;
{ int m,j,k;
  REAL value = 0.0;
  REAL val;
  REAL derivs[MAXCOORD];
  REAL detgrad[FACET_CTRL][MAXCOORD];
  REAL area,det;
  REAL ss,st,tt;

  for ( m = 0 ; m < FACET_CTRL ; m++ )
     for ( j = 0 ; j < SDIM ; j++ )
        f_info->grad[m][j] = 0.0;

  for ( m = 0 ; m < gauss2D_num ; m++ )
  { REAL **tang = f_info->sides[m];
    ss = SDIM_dot(tang[0],tang[0]);
    st = SDIM_dot(tang[0],tang[1]);
    tt = SDIM_dot(tang[1],tang[1]);
    det = ss*tt-st*st;
    if ( det <= 0.0 ) continue;
    area = sqrt(det)/2;
    f_info->gauss_pt[m][2*SDIM] = m;
    eval_all(METH_INSTANCE(f_info->method)->expr[0],f_info->gauss_pt[m],SDIM,&val,
                                                       derivs,f_info->id);
    value += gauss2Dwt[m]*area*val;

    for ( k = 0 ; k < FACET_CTRL ; k++ )
      for ( j = 0 ; j < SDIM ; j++ )
        detgrad[k][j] = 2*gpolypartial[m][0][k]*tang[0][j]*tt
                + ss*2*gpolypartial[m][1][k]*tang[1][j]
                - 2*st*(gpolypartial[m][0][k]*tang[1][j]
               + gpolypartial[m][1][k]*tang[0][j]);

    for ( k = 0 ; k < FACET_CTRL ; k++ )
      for ( j = 0 ; j < SDIM ; j++ )
        f_info->grad[k][j] += gauss2Dwt[m]*
          (val/sqrt(det)/4*detgrad[k][j] + area*derivs[j]*gpoly[m][k]);
  }

  return value;
}
