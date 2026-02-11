simplex_tiny_edges(min_len)
REAL min_len;
#endif
{
  int delcount = 0;
  int i,j,k;
  facet_id f_id;

  FOR_ALL_FACETS(f_id)
  { vertex_id *fv = get_facet_vertices(f_id);
     int del;


     if ( !(get_fattr(f_id) & ALLOCATED) ) continue;

     del = 0;
     for ( i = 0 ; i <= web.dimension ; i++ )
     { for ( j = i+1 ; j <= web.dimension ; j++ )
          { REAL *x = get_coord(fv[i]);
             REAL *y = get_coord(fv[j]);
             REAL dist;
             for ( k = 0, dist = 0.0 ; k < SDIM ; k++ )
                dist += (x[k]-y[k])*(x[k]-y[k]);
             dist = sqrt(dist);
             if ( dist >= min_len ) continue;

             del = simplex_delete_edge(fv[i],fv[j]);
             delcount += del;
             if ( del ) break;
          }
         if ( del ) break;
      }
  }
  if ( delcount ) top_timestamp = ++global_timestamp;
  return delcount;
}
