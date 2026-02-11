set_next_vertex_facet(v_id,f_id,ff_id)
      vertex_id v_id; facet_id f_id,ff_id;
{
   vertex_id *v = get_facet_vertices(f_id);
   facet_id *f = F_ELID(f_id,F_NEXT_VFACET_ATTR);
   int vmax = web.skel[FACET].ctrlpts;
   int i;
   for ( i = 0 ; i < vmax ; i++ )
   { if (equal_id(v_id,v[i]))
     { f[i] = ff_id ;
       break;
     }
   }
}
