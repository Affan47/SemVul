live_worklist (tree_live_info_p live)
{
  unsigned b;
  basic_block bb;
  sbitmap visited = sbitmap_alloc (last_basic_block + 1);
  bitmap tmp = BITMAP_ALLOC (&liveness_bitmap_obstack);

  bitmap_clear (visited);


  FOR_EACH_BB_REVERSE (bb)
    loe_visit_block (live, bb, visited, tmp);


  while (live->stack_top != live->work_stack)
    {
      b = *--(live->stack_top);
      loe_visit_block (live, BASIC_BLOCK (b), visited, tmp);
    }

  BITMAP_FREE (tmp);
  sbitmap_free (visited);
}
