constr_edge_energy_q(e_id)
edge_id e_id;
{
  REAL x[EDGE_CTRL][MAXCOORD];
  REAL *pt[EDGE_CTRL];
  REAL etang[MAXCOORD];
  vertex_id v[EDGE_CTRL];
  int i,j,k;
  struct constraint *constr;
  REAL energy = 0.0;
  REAL side[MAXCOORD];
  REAL green[MAXCOORD];
  conmap_t *conmap;
  int sign;
  REAL gpt[MAXCOORD];

  int_val = ordinal(get_original(e_id))+1;
  conmap = get_e_constraint_map(e_id);
  get_edge_side(e_id,side);
  if ( get_eattr(e_id) & NEGBOUNDARY ) sign = -1;
  else sign = 1;

  v[0] = get_edge_tailv(e_id);
  v[1] = get_edge_midv(e_id);
  v[2] = get_edge_headv(e_id);
  for ( i = 0 ; i < EDGE_CTRL ; i++ )
    pt[i] = get_coord(v[i]);

  for ( i = 0 ; i < EDGE_CTRL ; i++ )
     for ( j = 0 ; j < SDIM ; j++ )
        x[i][j] = pt[i][j];


  for ( i = 0 ; i < EDGE_INTERP ; i++ )
  { for ( j = 0 ; j < SDIM ; j ++ )
    { etang[j] = 0.0;
      gpt[j] = 0.0;
      for ( k = 0 ; k < EDGE_CTRL ; k++ )
      { etang[j] += sdip[k][i]*x[k][j];
        gpt[j] += gcombo[k][i]*x[k][j];
      }
    }
    for ( j = 1 ; j <= (int)conmap[0] ; j++ )
    { constr = get_constraint(conmap[j]);
      if ( !(constr->attr & CON_ENERGY) ) continue;
      if ( constr->compcount != SDIM ) continue;
      for ( k = 0 ; k < SDIM ; k++ )
        green[k] = eval(constr->envect[k],gpt,e_id,NULL);
      energy += sign*gauss2wt[i]*SDIM_dot(etang,green);
    }
  }

  binary_tree_add(web.total_energy_addends,energy);

}
