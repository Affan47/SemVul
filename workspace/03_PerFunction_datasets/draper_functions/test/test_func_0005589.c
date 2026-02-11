set_fe_facet(fe_id,f_id)
facetedge_id fe_id;
facet_id f_id;
{ facet_id oldf = get_fe_facet(fe_id);

  feptr(fe_id)->fe_facet_id = inverted(fe_id) ? inverse_id(f_id) : f_id;

  if ( web.representation==STRING && everything_quantities_flag &&
        !equal_id(oldf,f_id) )
  {
     body_id b_id, old_b_id;
     edge_id e_id = get_fe_edge(fe_id);
     b_id = get_facet_body(f_id);

     old_b_id = valid_id(oldf) ? get_facet_body(oldf) : NULLID;
     if ( valid_id(old_b_id) )
        unapply_method(e_id,get_body_volmeth(old_b_id));
     old_b_id = valid_id(oldf) ? get_facet_body(inverse_id(oldf)) : NULLID;
     if ( valid_id(old_b_id) )
        unapply_method(e_id,get_body_volmeth(old_b_id));


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
}
