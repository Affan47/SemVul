ridge_notcher(max_angle)
REAL max_angle;
{
  int notchcount = 0;
  edge_id e_id;
  facet_id *todo;
  int i;
  int maxfacet = web.skel[FACET].max_ord+1;
  edge_id sentinel;

  web.vol_flag = 0;

  todo = (facet_id *)temp_calloc(web.skel[FACET].max_ord+1,sizeof(facet_id));


  FOR_ALL_EDGES(e_id)
      unset_attr(e_id,NEWEDGE);


  e_id = NULLEDGE;
  while ( generate_all(EDGE,&e_id,&sentinel) )
  { REAL angle;
    facetedge_id fe_a;
    facet_id f_id;

    if ( get_eattr(e_id) & (FIXED | BOUNDARY | NEWEDGE) )
        continue;

    angle = dihedral(e_id);
    if ( angle < max_angle )
      continue;


    fe_a = get_edge_fe(e_id);
    f_id = get_fe_facet(fe_a);
    todo[loc_ordinal(f_id)] = f_id;
    f_id = get_fe_facet(get_next_facet(fe_a));
    todo[loc_ordinal(f_id)] = f_id;
    if ( verbose_flag )
    { sprintf(msg,"Notching edge %s\n",ELNAME(e_id));
      outstring(msg);
    }

  }

  for ( i = 0 ; i < maxfacet ; i++ )
     if ( valid_id(todo[i]) )
        { face_triangulate(todo[i],FACET_EDGES);
          notchcount++;
        }
  temp_free((char*)todo);

  if ( notchcount > 0 ) top_timestamp = ++global_timestamp;
  return notchcount;
}
