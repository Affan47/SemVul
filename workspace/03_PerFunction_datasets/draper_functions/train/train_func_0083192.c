q_edge_setup_lagrange(e_info,needs)
struct qinfo *e_info;
int needs;
{ int i;
  int ctrl = web.skel[EDGE].ctrlpts;
  int dim = (web.representation==STRING) ? 1 : web.dimension - 1 ;
  struct gauss_lag *gl = &gauss_lagrange[dim][web.gauss1D_order];
  vertex_id *v;


  e_info->vcount = ctrl;
  v = get_edge_vertices(e_info->id);
  if ( inverted(e_info->id) )
  for ( i = 0 ; i < ctrl ; i++ )
  { e_info->v[i] = v[ctrl-i-1];
    e_info->x[i] = get_coord(v[ctrl-i-1]);
  }
  else
  for ( i = 0 ; i < ctrl ; i++ )
  { e_info->v[i] = v[i];
    e_info->x[i] = get_coord(v[i]);
  }
  if ( web.symmetry_flag )
  { WRAPTYPE wrap = get_edge_wrap(e_info->id);
    (*sym_wrap)(e_info->x[ctrl-1],e_info->xx[ctrl-1],wrap);
    e_info->x[ctrl-1] = e_info->xx[ctrl-1];
    e_info->wraps[ctrl-1] = wrap;
  }
  if ( needs & NEED_SIDE )
  {
    int m;
    for ( m = 0 ; m < gl->gnumpts ; m++ )
      mat_mult(gl->gpolypart[m],e_info->x,e_info->sides[m],dim,ctrl,SDIM);
  }
  if ( needs & NEED_WINGS )
  { kb_error(1576,
     "Can't do Lagrange model with WINGS (needed for some method instance).\n",
        RECOVERABLE);
  }
  if ( needs & NEED_GAUSS )
     mat_mult(gl->gpoly,e_info->x,e_info->gauss_pt,gl->gnumpts,ctrl,SDIM);
}
