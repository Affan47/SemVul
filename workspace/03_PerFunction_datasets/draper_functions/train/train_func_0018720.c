facet_volume_l(f_id)
facet_id f_id;
{
  body_id b_id0,b_id1;
  facetedge_id fe_id;
  REAL vol;

  if ( get_fattr(f_id) & NONCONTENT ) return;

  int_val = ordinal(get_original(f_id))+1;
  b_id0 = get_facet_body(f_id);
  b_id1 = get_facet_body(facet_inverse(f_id));
  if ( !valid_id(b_id0) && !valid_id(b_id1) ) return;

  if ( web.symmetric_content )
  { vertex_id v1,v2,v3;
    facetedge_id next_fe;
    fe_id = get_facet_fe(f_id);
    next_fe = get_next_edge(fe_id);
    v1 = get_fe_tailv(fe_id);
    v2 = get_fe_headv(fe_id);
    v3 = get_fe_headv(next_fe);
    vol = triple_prod(get_coord(v1), get_coord(v2), get_coord(v3))/6;
  }
  else
  { MAT2D(x,MAXCOORD,MAXCOORD);
    get_facet_verts(f_id,x,NULL);
    vol = (x[0][2]+x[1][2]+x[2][2])/6*
     ((x[1][0]-x[0][0])*(x[2][1]-x[0][1])-(x[1][1]-x[0][1])*(x[2][0]-x[0][0]));
  }


  if ( valid_id(b_id0) )
    add_body_volume(b_id0,vol);

  if ( valid_id(b_id1) )
    add_body_volume(b_id1,-vol);

}
