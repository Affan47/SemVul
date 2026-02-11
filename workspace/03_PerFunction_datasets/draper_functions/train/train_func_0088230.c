sqgauss_method_grad(v_info)
struct qinfo *v_info;
{
  REAL modulus = sqgauss_flag ? globals(sqgauss_param)->value.real : 0.0;
  vertex_id v_id;
  edge_id e_id,start_e;
  int j;
  REAL gc;
  REAL energy = 0.0;


  v_id = v_info->id;
  gv = gverts + loc_ordinal(v_id);
  if ( get_vattr(v_id) & (FIXED|BOUNDARY) ) return 0.0;
  gc = (wedge_angle(v_id) - gv->angle)/gv->area;
  energy += modulus*gc*gc*gv->star_area;
  gv->gc = gc;


  for ( j = 0 ; j < SDIM ; j++ )
     v_info->grad[0][j] += (2*gc*gv->star_area*(-gv->angle_grad[j]/gv->area
                         - gc*gv->area_grad[j]/gv->area)
                         + gc*gc*gv->star_area_grad[j])*modulus;


  start_e = e_id = get_vertex_edge(v_id);
  if ( !(get_vattr(v_id) & (FIXED|BOUNDARY) ) )
    do
    {
      struct gvert *gv2 = gverts + loc_ordinal(get_edge_headv(e_id));
      struct gedge *ge = gedges + loc_ordinal(e_id);


        for ( j = 0 ; j < SDIM ; j++ )
             v_info->grad[0][j] +=
                    (2*gv2->gc*gv2->star_area*(-ge->angle_grad[0][j]/gv2->area
                        - gv2->gc*ge->area_grad[0][j]/gv2->area)
                        + gv2->gc*gv2->gc*ge->star_area_grad[0][j])*modulus;

      e_id = get_next_tail_edge(e_id);
    } while ( !equal_element(start_e,e_id) );

 return energy;
}
