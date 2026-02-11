sort_edge_points(ntuple_ll se, ntuple_list ls)
{
  unsigned int i,j,n;
  struct point * p;
  double theta;

  for(i=0; i<se->size; i++)
    {
      n = se->list[i]->size;


      p = (struct point *) calloc( (size_t) n, sizeof(struct point) );
      if( p == NULL ) error("not enough memory!");


      for(j=0;j<n;j++)
        {
          p[j].x = se->list[i]->values[ j*2 + 0 ];
          p[j].y = se->list[i]->values[ j*2 + 1 ];
        }


      theta = atan( ( ls->values[ i * ls->dim + 3 ]
	      - ls->values[ i * ls->dim + 1 ] ) /
	    ( ls->values[ i * ls->dim + 2 ]
	      - ls->values[ i * ls->dim + 0 ] ) );
      if( theta < (M_PI / 4.0)  && theta > (-M_PI / 4.0))
        qsort( (void *)p, n, sizeof(struct point), &comp_point_x );
      else if (theta >= (M_PI / 4.0))
        qsort( (void *)p, n, sizeof(struct point), &comp_point_y );
      else if (theta <= -(M_PI / 4.0))
        qsort( (void *)p, n, sizeof(struct point), &comp_point_y_decrease );
      else
	error("[straight_edge_points]: theta error!\n");


      for(j=0;j<n;j++)
        {
          se->list[i]->values[ j*2 + 0 ] = p[j].x;
          se->list[i]->values[ j*2 + 1 ] = p[j].y;
        }


      free( (void *) p );
    }
}
