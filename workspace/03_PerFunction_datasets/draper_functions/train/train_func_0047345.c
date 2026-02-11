Estimate_GCell_Population( reax_system* system, MPI_Comm comm )
{
  int d, i, j, k, l, max_atoms, my_max, all_max;
  ivec c;
  grid *g;
  grid_cell *gc;
  simulation_box *big_box, *my_ext_box;
  reax_atom *atoms;

  big_box    = &(system->big_box);
  my_ext_box = &(system->my_ext_box);
  g          = &(system->my_grid);
  atoms      = system->my_atoms;
  Reset_Grid( g );

  for( l = 0; l < system->n; l++ ) {
    for( d = 0; d < 3; ++d ) {


      c[d] = (int)((atoms[l].x[d]-my_ext_box->min[d])*g->inv_len[d]);

      if( c[d] >= g->native_end[d] )
        c[d] = g->native_end[d] - 1;
      else if( c[d] < g->native_str[d] )
        c[d] = g->native_str[d];
    }
#if defined(DEBUG)
    fprintf( stderr, "p%d bin_my_atoms: l:%d - atom%d @ %.5f %.5f %.5f"        \
             "--> cell: %d %d %d\n",
             system->my_rank, l, atoms[l].orig_id,
             atoms[l].x[0], atoms[l].x[1], atoms[l].x[2],
             c[0], c[1], c[2] );
#endif
    gc = &( g->cells[c[0]][c[1]][c[2]] );
    gc->top++;
  }

  max_atoms = 0;
  for( i = 0; i < g->ncells[0]; i++ )
    for( j = 0; j < g->ncells[1]; j++ )
      for( k = 0; k < g->ncells[2]; k++ ) {
        gc = &(g->cells[i][j][k]);
        if( max_atoms < gc->top )
          max_atoms = gc->top;
#if defined(DEBUG)
        fprintf( stderr, "p%d gc[%d,%d,%d]->top=%d\n",
                 system->my_rank, i, j, k, gc->top );
#endif
      }

  my_max = (int)(MAX(max_atoms*SAFE_ZONE, MIN_GCELL_POPL));
  MPI_Allreduce( &my_max, &all_max, 1, MPI_INT, MPI_MAX, comm );
#if defined(DEBUG)
  fprintf( stderr, "p%d max_atoms=%d, my_max=%d, all_max=%d\n",
           system->my_rank, max_atoms, my_max, all_max );
#endif

  return all_max;
}
