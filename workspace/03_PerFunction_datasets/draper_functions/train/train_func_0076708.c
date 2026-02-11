klein_area_method(f_info)
struct qinfo *f_info;
{
  REAL area;
  int i;
  int     v;
  int     s;
  REAL **triangle = f_info->x;

  REAL coshs[MAXCOORD],
       sinhs[MAXCOORD],
       coss[MAXCOORD];

  for ( s = 0 ; s < 3 ; s++ )
  { coshs[s] = coshKleinLength(triangle[(s+1)%3], triangle[(s+2)%3]);
    sinhs[s] = sqrt(coshs[s]*coshs[s] - 1);
    if ( sinhs[s] == 0.0  ) return 0.0;
  }
  for(v=0;v<3;v++)
      coss[v] = (coshs[(v+1)%3]*coshs[(v+2)%3] - coshs[v]) /
             sinhs[(v+1)%3]/sinhs[(v+2)%3];

  area = M_PI;
  for(i=0;i<3;i++)
     area -= acos(coss[i]);

  if ( everything_quantities_flag  &&
      (METH_INSTANCE(f_info->method)->quant == default_area_quant_num) )
     area *= get_facet_density(f_info->id);

  return(area);
}
