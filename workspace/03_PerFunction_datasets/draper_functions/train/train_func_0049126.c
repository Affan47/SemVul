get_simplex_next_vertex_facet(v_id,f_id)
vertex_id v_id;
facet_id f_id;
{ int i;
  vertex_id *v = get_facet_vertices(f_id);
  facet_id *f = F_ELID(f_id,F_NEXT_VFACET_ATTR);
  int vmax = web.skel[FACET].ctrlpts;

  for ( i = 0 ; i < vmax ; i++ )
     if (equal_id(v_id,v[i]))  return f[i] ;
  sprintf(errmsg,"Internal error: get_next_vertex_facet failure v %s f %s\n",
      ELNAME(v_id), ELNAME1(f_id));
  kb_error(1306,errmsg,RECOVERABLE);

  return NULLID;
}
