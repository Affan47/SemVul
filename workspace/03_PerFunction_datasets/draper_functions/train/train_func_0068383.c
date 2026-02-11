facetedge_dump(fe,fd)
facetedge_id fe;
FILE *fd;
{ edge_id e_id;
  facet_id f_id;
  facetedge_id nf = get_next_facet(fe);
  facetedge_id pf = get_prev_facet(fe);
  facetedge_id ne = get_next_edge(fe);
  facetedge_id pe = get_prev_edge(fe);
  FILE *old_fd = outfd;
  int i;
  struct extra *ex;
  outfd = fd;

  e_id = get_fe_edge(fe);
  f_id = get_fe_facet(fe);
  sprintf(msg,"%6s      %5s    %5s  %8s %8s     %8s %8s",
      ELNAME(fe), SELNAME1(e_id), SELNAME2(f_id),
      (valid_id(pe) ? SELNAME3(pe) : "0"),
      (valid_id(ne) ? SELNAME4(ne) : "0"),
      (valid_id(pf) ? SELNAME5(pf) : "0"),
      (valid_id(nf) ? SELNAME6(nf) : "0"));
  outstring(msg);


  for ( i = 0, ex = EXTRAS(FACETEDGE) ;
                i < web.skel[FACETEDGE].extra_count; i++,ex++ )
    { char *at = get_extra(fe,i);
      if ( !(ex->flags & DUMP_ATTR) ) continue;
      if ( ex->array_spec.datacount == 0 ) continue;
      sprintf(msg," %s ",ex->name);
      print_array_attribute(ex,at);
    }
  outstring("\n");
  outfd = old_fd;
}
