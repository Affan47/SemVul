test_axial_points(f_id)
facet_id f_id;
{ facetedge_id fe;
  int i;

  if ( inverted(f_id) ) f_id = inverse_id(f_id);
  fe = get_facet_fe(f_id);
  for ( i = 0 ; i < FACET_EDGES ; i++ )
  { vertex_id v_id;
    v_id = get_fe_tailv(fe);
    if ( get_vattr(v_id) & AXIAL_POINT )
    { set_facet_fe(f_id,fe); return; }
    fe = get_next_edge(fe);
  }
}
