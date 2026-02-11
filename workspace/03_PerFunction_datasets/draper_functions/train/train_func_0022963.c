compare_edge_facet_attr(ea,fb)
edge_id ea;
facet_id fb;
{ int i,j;
  conmap_t * con1,*con2;
  int fixa = get_eattr(ea) & FIXED;
  int fixb = get_fattr(fb) & FIXED;
  int same = 0;


  con1 = get_e_constraint_map(ea);
  con2 = get_f_constraint_map(fb);

  for ( i = 1 ; i <= (int)con2[0] ; i++ )
  { for ( j = 1 ; j <= (int)con1[0] ; j++ )
      if ( (con1[j]&CONMASK) == (con2[i]&CONMASK) )
      { same++;
        break;
      }
  }

  if ( (same==(int)con1[0]) && (same==(int)con2[0])&& !fixa && !fixb )
    return A_EQ_B;
  if ( (same==(int)con1[0]) && (same < (int)con2[0]) && !fixa )
    return A_SUB_B;
  if ( (same < (int)con1[0]) && (same==(int)con2[0]) && !fixb )
    return A_SUPER_B;
  return INCOMPARABLE;

}
