new_facetedge(f_id,e_id)
facet_id f_id;
edge_id e_id;
{
  facetedge_id fe_id;

  fe_id = new_element(FACETEDGE,NULLID,NULLID);
  set_fe_edge(fe_id,e_id);
  set_fe_facet(fe_id,f_id);
  set_prev_edge(fe_id,NULLFACETEDGE);
  set_next_edge(fe_id,NULLFACETEDGE);
  set_prev_facet(fe_id,NULLFACETEDGE);
  set_prev_facet(fe_id,NULLFACETEDGE);
  #ifndef MPI_EVOLVER
  { vertex_id headv,tailv;
    tailv = get_edge_tailv(e_id);
    headv = get_edge_headv(e_id);
    if ( !valid_id(get_vertex_edge(tailv)) )
      set_vertex_edge(tailv,e_id);
    if ( !valid_id(get_vertex_edge(headv)) )
      set_vertex_edge(headv,e_id);
  }
  #endif

  if ( web.representation==STRING && everything_quantities_flag )
  {
     body_id b_id;
     b_id = get_facet_body(f_id);
     if ( valid_id(b_id) )
     { if ( same_sign(f_id,e_id) )
          apply_method_num(e_id,get_body_volmeth(b_id));
        else
          apply_method_num(inverse_id(e_id),get_body_volmeth(b_id));
     }
     b_id = get_facet_body(inverse_id(f_id));
     if ( valid_id(b_id) )
     { if ( same_sign(f_id,e_id) )
          apply_method_num(inverse_id(e_id),get_body_volmeth(b_id));
        else
          apply_method_num(e_id,get_body_volmeth(b_id));
     }
  }
  return fe_id;
}
