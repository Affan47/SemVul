Deallocate_Grid( grid *g )
{
  int i, j, k;
  grid_cell *gc;

  sfree( g->order, "g:order" );


  for( i = 0; i < g->ncells[0]; i++ ) {
    for( j = 0; j < g->ncells[1]; j++ ) {
      for( k = 0; k < g->ncells[2]; k++ ) {
        gc = &(g->cells[i][j][k]);
        sfree( gc->nbrs, "g:nbrs" );
        sfree( gc->nbrs_x, "g:nbrs_x" );
        sfree( gc->nbrs_cp, "g:nbrs_cp" );
        if(gc->atoms != NULL )
          sfree( gc->atoms, "g:atoms" );
      }
      sfree( g->cells[i][j], "g:cells[i][j]" );
    }
    sfree( g->cells[i], "g:cells[i]" );
  }
  sfree( g->cells, "g:cells" );
}
