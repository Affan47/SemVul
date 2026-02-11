grid_store_delete(grid_store_t *grid_store)
{
  grid_layer_t *grid_layer, *grid_layer_f;
  long ilayer;
  long i, j;
  long iblk;

  for ( iblk = 0; iblk < grid_store->nblocks; ++iblk )
    {
      j = 0;
      grid_layer = grid_store->layers[iblk];
      for ( ilayer = 0; ilayer < grid_store->nlayers[iblk]; ++ilayer )
	{
	  if ( cdoVerbose )
	    {
	      for ( i = 0; i < grid_store->blksize[iblk]; ++i )
		if ( grid_layer->grid2_link[i] != -1 ) j++;
	    }

	  grid_layer_f = grid_layer;
	  free(grid_layer->grid2_link);
	  grid_layer = grid_layer->next;
	  free(grid_layer_f);
	}

      if ( cdoVerbose )
	{
	  fprintf(stderr, "block = %ld nlayers = %d  allocated = %d  used = %ld\n",
		  iblk+1, grid_store->nlayers[iblk],
		  grid_store->nlayers[iblk]*grid_store->blksize[iblk], j);
	}
    }

  free(grid_store->blksize);
  free(grid_store->layers);
  free(grid_store->nlayers);
}
