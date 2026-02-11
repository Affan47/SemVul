facet_energy_q(f_id,mode)
facet_id f_id;
int mode;
{
  REAL energy = 0.0;
  body_id b_id;
  MAT2D(x,FACET_CTRL,MAXCOORD);
  vertex_id v_id[FACET_CTRL];
  REAL normal[MAXCOORD];
  int i,j;
  REAL norm;
  facetedge_id fe_id;
  REAL u = 0.0;
  REAL z;
  WRAPTYPE wraps[FACET_CTRL];
  MAT2D(tang,MAXCOORD,MAXCOORD);


  get_facet_verts(f_id,x,wraps);

  if ( web.metric_flag )
  { energy = simplex_energy_metric(v_id,x);
    goto skip_from_metric;
  }

  for ( i = 0 ; i < gauss2D_num ; i++ )
  {

    mat_mult(gpolypartial[i],x,tang,web.dimension,ctrl_num,SDIM);
    cross_prod(tang[0],tang[1],normal);
    norm = sqrt(SDIM_dot(normal,normal));
    energy += gauss2Dwt[i]*norm/2;

    if ( web.gravflag && !(get_fattr(f_id) & NONCONTENT) )
    { z = 0.0;
      for ( j = 0 ; j < FACET_CTRL ; j++ )
        z += gpoly[i][j]*x[j][2];
      u += 0.5*z*z*gauss2Dwt[i]/2*(tang[0][0]*tang[1][1] -
                                                    tang[0][1]*tang[1][0]);
    }
  }

skip_from_metric:
  set_facet_area(f_id,energy);

  if ( mode == AREA_ONLY ) return;

  binary_tree_add(web.total_area_addends,energy);


  { fe_id = get_facet_fe(f_id);
    for ( i = 0 ; i < FACET_EDGES ; i++, fe_id = get_next_edge(fe_id) )
    { vertex_id vv_id;
      edge_id e_id = get_fe_edge(fe_id);
      vv_id = get_edge_headv(e_id);
      add_vertex_star(vv_id,energy);
      vv_id = get_edge_midv(e_id);
      add_vertex_star(vv_id,energy);
    }
  }


  energy *= get_facet_density(f_id);


  if ( web.gravflag && !(get_fattr(f_id) & NONCONTENT) )
  { b_id = get_facet_body(f_id);
    if ( valid_id(b_id) )
       energy += u*get_body_density(b_id)*web.grav_const;
    b_id = get_facet_body(facet_inverse(f_id));
    if ( valid_id(b_id) )
       energy -= u*get_body_density(b_id)*web.grav_const;
  }

  web.total_energy = web.total_energy + energy;

}
