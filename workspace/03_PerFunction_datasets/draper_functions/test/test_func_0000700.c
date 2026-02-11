q_edge_area(e_info)
struct qinfo *e_info;
{ REAL **x;
  REAL area;

  if ( web.torus_flag ) area = q_edge_torus_area(e_info);
  else if ( web.modeltype == QUADRATIC ) area = q_edge_area_q(e_info);
  else if ( web.modeltype == LAGRANGE )  area = q_edge_area_lagrange(e_info);
  else
  { x = e_info->x;


    area = (x[0][1]+x[1][1])*(x[0][0] - x[1][0])/2;
  }

  if ( METH_INSTANCE(e_info->method)->flags & DEFAULT_INSTANCE )
  {
    body_id b_id,bb_id;
    facetedge_id fe_id = get_edge_fe(e_info->id);
    facetedge_id fe;
    facet_id f_id;

    b_id = GEN_QUANT(METH_INSTANCE(e_info->method)->quant)->b_id;
    fe = fe_id;
    do
    { f_id = get_fe_facet(fe);
      bb_id = get_facet_body(f_id);
      if ( equal_id(b_id,bb_id) )
         add_facet_area(f_id,area);
      bb_id = get_facet_body(inverse_id(f_id));
      if ( equal_id(b_id,bb_id) )
         add_facet_area(f_id,area);
      fe = get_next_facet(fe);
    } while ( !equal_id(fe,fe_id) );
  }

  return area;
}
