facet_scalar_integral_q(f_info)
struct qinfo *f_info;
{ int m;
  REAL value = 0.0;
  REAL area;
  REAL ss,st,tt;

  for ( m = 0 ; m < gauss2D_num ; m++ )
  { REAL **tang = f_info->sides[m];
    ss = SDIM_dot(tang[0],tang[0]);
    st = SDIM_dot(tang[0],tang[1]);
    tt = SDIM_dot(tang[1],tang[1]);
    area = ss*tt-st*st;
    if ( area <= 0.0 ) continue;
    f_info->gauss_pt[m][2*SDIM] = m;
    value += gauss2Dwt[m]*sqrt(area)*
       eval(METH_INSTANCE(f_info->method)->expr[0],f_info->gauss_pt[m],f_info->id,NULL);
  }
  return value/2;
}
