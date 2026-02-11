body_facet_fixup(facet)
facet_id facet;
{
  body_id b_id;
  facet_id bf_id;
  facet_id f_id;


  if ( valid_id(facet) )
  { b_id = get_facet_body(facet);
    bf_id = get_body_facet(b_id);
    if ( equal_element(facet,bf_id) )
    {
      set_body_facet(b_id,NULLID);
      FOR_ALL_FACETS(f_id)
      { if ( equal_element(f_id,facet) ) continue;
        if ( equal_id(get_facet_body(f_id),b_id) )
        { set_body_facet(b_id,f_id); break; }
        if ( equal_id(get_facet_body(inverse_id(f_id)),b_id) )
        { set_body_facet(b_id,inverse_id(f_id)); break; }
      }
    }
    b_id = get_facet_body(inverse_id(facet));
    bf_id = get_body_facet(b_id);
    if ( equal_element(facet,bf_id) )
    {
      set_body_facet(b_id,NULLID);
      FOR_ALL_FACETS(f_id)
      { invert(f_id);
        if ( equal_element(f_id,facet) ) continue;
        if ( equal_id(get_facet_body(f_id),b_id) )
        { set_body_facet(b_id,f_id); break; }
        if ( equal_id(get_facet_body(inverse_id(f_id)),b_id) )
        { set_body_facet(b_id,inverse_id(f_id)); break; }
      }
    }
  }
}
