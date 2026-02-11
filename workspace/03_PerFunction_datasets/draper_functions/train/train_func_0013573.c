edge_energy_hessian(S,rhs)
struct linsys *S;
REAL *rhs;
{ int i,j;
  int head,tail;
  edge_id e_id;
  MAT2D(first,2,MAXCOORD);
  MAT4D(second,2,2,MAXCOORD,MAXCOORD);


    FOR_ALL_EDGES(e_id)
     {
        struct hess_verlist *v[MAXCOORD];
        vertex_id *v_id = get_edge_vertices(e_id);

        if ( ! get_e_constraint_map(e_id)[0] ) continue;

        for ( i = 0 ; i < 2 ; i++ )
          v[i] = get_vertex_vhead(v_id[i]);

        memset((char*)first[0],0,sizeof(REAL)*2*MAXCOORD);
        memset((char*)second[0][0][0],0,sizeof(REAL)*2*2*MAXCOORD*MAXCOORD);

        edge_constr_hessian(S,e_id,first,second);


        for ( i = 0 ; i < 2 ; i++ )
         fill_grad(S,v[i],first[i],rhs);

        if ( hess_flag )
         for ( i = 0 ; i < 2 ; i++ )
          for ( j = i ; j < 2 ; j++ )
          {
             if ( (v[i]->freedom==0) || (v[j]->freedom==0) ) continue;
             if ( loc_ordinal(v_id[i]) > loc_ordinal(v_id[j]) )
                 { tail = i; head = j; }
             else { tail = j; head = i; }

             fill_mixed_entry(S,v_id[tail],v_id[head],second[tail][head]);
            }
      }
}
