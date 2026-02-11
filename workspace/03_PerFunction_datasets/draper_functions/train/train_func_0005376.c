wrap_vertex(v_id,wrap)
vertex_id v_id;
int wrap;
{ int i;
  REAL newx[MAXCOORD];
  REAL *x = get_coord(v_id);
  edge_id e_id,start_e;

  if ( (web.modeltype != LINEAR) && (web.modeltype != QUADRATIC) )
    kb_error(4323,
      "Can only do vertex wrap in LINEAR and QUADRATIC models so far.\n",
         RECOVERABLE);

  if ( !web.symmetry_flag ) return;
  if ( get_vattr(v_id) & (Q_MIDPOINT|Q_MIDEDGE|Q_MIDFACET) ) return;

  ENTER_GRAPH_MUTEX;
  sym_wrap(x,newx,wrap);
  for ( i = 0 ; i < SDIM ; i++ ) x[i] = newx[i];
  start_e = e_id = get_vertex_edge(v_id);
  do
  { set_edge_wrap(e_id,sym_compose(wrap,get_edge_wrap(e_id)));
    if ( (web.modeltype == QUADRATIC) && !inverted(e_id) )
    { x = get_coord(get_edge_midv(e_id));
      sym_wrap(x,newx,wrap);
      for ( i = 0 ; i < SDIM ; i++ ) x[i] = newx[i];
    }
    e_id = get_next_tail_edge(e_id);
  } while ( !equal_id(start_e,e_id) );
  LEAVE_GRAPH_MUTEX;
}
