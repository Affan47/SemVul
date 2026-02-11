q_edge_area_grad(e_info)
struct qinfo *e_info;
{ REAL **x,**g;
  REAL area;

  if ( web.torus_flag ) return q_edge_torus_area_grad(e_info);
  if ( web.modeltype == QUADRATIC ) return q_edge_area_q_grad(e_info);
  if ( web.modeltype == LAGRANGE ) return q_edge_area_lagrange_grad(e_info);

  x = e_info->x;
  g = e_info->grad;


  area = (x[0][1]+x[1][1])*(x[0][0] - x[1][0])/2;
  g[0][0] = (x[1][1] + x[0][1])/2;
  g[1][0] = -(x[1][1] + x[0][1])/2;
  g[0][1] = (x[0][0] - x[1][0])/2;
  g[1][1] = (x[0][0] - x[1][0])/2;
  return area;
}
