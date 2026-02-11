binary_OFF_facet(gdata,f_id)
struct graphdata *gdata;
facet_id f_id;
{
  int i,k;
  struct graphdata ggdata[2];

  if ( OFF_vertex_count > OFF_verts_alloc - 5 )
  { OFF_verts = (struct OFF_vertex_t*)temp_realloc((char*)OFF_verts,
        2*OFF_verts_alloc*sizeof(struct OFF_vertex_t));
    OFF_verts_alloc *= 2;
  }
  if ( OFF_facet_count > OFF_facets_alloc - 5 )
  { OFF_facets = (struct OFF_facet_t*)temp_realloc((char*)OFF_facets,
        2*OFF_facets_alloc*sizeof(struct OFF_facet_t));
    OFF_facets_alloc *= 2;
  }


  for ( i = 0 ; i < FACET_VERTS ; i++ )
  { for ( k = 0 ; k < 3 ; k++ )
      OFF_verts[OFF_vertex_count].x[k] = gdata[i].x[k];
    OFF_facets[OFF_facet_count].v[i] = OFF_vertex_count;
    OFF_vertex_count++;
  }
  OFF_facets[OFF_facet_count].color = gdata[0].color;
  OFF_facet_count++;


  for ( i = 0 ; i < FACET_EDGES ; i++ )
  { if ( ((gdata[i].etype&EBITS)|REGULAR_EDGE) == REGULAR_EDGE ) continue;
    ggdata[0] = gdata[i];
    ggdata[0].color = gdata[i].ecolor;
    ggdata[1] = gdata[i==2 ? 0 : i+1];
    binary_OFF_edge(ggdata,NULLID);
  }
}
