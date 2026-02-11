klein_length_method_grad(e_info)
struct qinfo *e_info;
{
  int i;
  REAL aa,bb,ab,den,disc;
  REAL *head = e_info->x[1];
  REAL *tail = e_info->x[0];
  REAL fudge;
  if ( everything_quantities_flag  &&
      (METH_INSTANCE(e_info->method)->quant == default_area_quant_num) )
     fudge = get_edge_density(e_info->id);
  else fudge = 1.0;


  aa = 1 - SDIM_dot(head,head);
  bb = 1 - SDIM_dot(tail,tail);
  ab = 1 - SDIM_dot(head,tail);
  disc = ab*ab - aa*bb;
  if ( disc == 0.0 )
  { kb_error(3359,"Vertices outside Klein disk, or zero length edge.\n",
         WARNING); return 0.0;
  }
  if ( disc < 0.0 )
  { kb_error(1665,"Vertices outside Klein disk.\n",WARNING); return 0.0; }

  den = sqrt(disc);
  for ( i = 0 ; i < SDIM ; i++ )
  { e_info->grad[1][i] += fudge*(ab*head[i]/aa - tail[i])/den;
    e_info->grad[0][i] += fudge*(ab*tail[i]/bb - head[i])/den;
  }
  return(fudge*kb_acosh(coshKleinLength(head, tail)));
}
