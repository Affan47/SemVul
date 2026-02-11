local_calc_content ARGS1((mode),
int mode)
{
  facet_id  f_id;
  facetedge_id fe_id;
  body_id b_id;

  FOR_ALL_BODIES(b_id)
  {
    struct body *ptr;
	int k;

	ptr = bptr(b_id);
    for ( k = 0 ; k < MAXADDENDS ; k++ )
       ptr->volume_addends[k] = 0;
  }

  if ( gen_quant_count )
     calc_quants(mode);

  if ( quantities_only_flag ) return;
  if ( web.bodycount == 0 ) return;

  if ( web.representation == SIMPLEX )
  { FOR_ALL_FACETS(f_id)
      calc_simplex_volume(f_id);
  }
  else if ( web.representation == STRING )
  { vertex_id v_id;

    FOR_ALL_FACETEDGES(fe_id)
      (*calc_edge_area)(fe_id);

    FOR_ALL_VERTICES(v_id)
    { ATTR attr = get_vattr(v_id);
      if ( !(attr & BDRY_CONTENT) ) continue;
      if ( attr & CONSTRAINT )
         calc_constr_content_v(v_id);
    }
  }

  else if ( web.representation == SOAPFILM )
  { if ( web.torus_flag ) torvol();
    else
    { edge_id e_id;

      FOR_ALL_FACETS(f_id)
        (*calc_facet_volume)(f_id);

      FOR_ALL_EDGES(e_id)
      { ATTR attr = get_eattr(e_id);
        if ( !(attr & BDRY_CONTENT) ) continue;
        if ( attr & CONSTRAINT )
          calc_constr_content_e(e_id);
      }
    }
  }


  FOR_ALL_BODIES(b_id)
  { REAL sum = 0.0;
    struct body *ptr = bptr(b_id);
	int k;
    for ( k = 0 ; k < MAXADDENDS ; k++ )
      sum += ptr->volume_addends[k];
    add_body_volume_plain(b_id,sum);
  }

}
