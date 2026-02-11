tm_region_init (struct tm_region *region)
{
  gimple g;
  edge_iterator ei;
  edge e;
  basic_block bb;
  vec<basic_block> queue = vNULL;
  bitmap visited_blocks = BITMAP_ALLOC (NULL);
  struct tm_region *old_region;
  vec<tm_region_p> bb_regions = vNULL;

  all_tm_regions = region;
  bb = single_succ (ENTRY_BLOCK_PTR);


  bb_regions.safe_grow_cleared (last_basic_block);

  queue.safe_push (bb);
  bb_regions[bb->index] = region;
  do
    {
      bb = queue.pop ();
      region = bb_regions[bb->index];
      bb_regions[bb->index] = NULL;


      region = tm_region_init_1 (region, bb);


      g = last_stmt (bb);
      old_region = region;
      if (g && gimple_code (g) == GIMPLE_TRANSACTION)
	region = tm_region_init_0 (region, bb, g);


      FOR_EACH_EDGE (e, ei, bb->succs)
	if (!bitmap_bit_p (visited_blocks, e->dest->index))
	  {
	    bitmap_set_bit (visited_blocks, e->dest->index);
	    queue.safe_push (e->dest);


	    if (old_region != region && e->dest != region->entry_block)
	      bb_regions[e->dest->index] = old_region;
	    else
	      bb_regions[e->dest->index] = region;
	  }
    }
  while (!queue.is_empty ());
  queue.release ();
  BITMAP_FREE (visited_blocks);
  bb_regions.release ();
}
