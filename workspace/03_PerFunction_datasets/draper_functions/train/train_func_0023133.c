dfs_find_deadend (basic_block bb)
{
  sbitmap visited = sbitmap_alloc (last_basic_block);
  sbitmap_zero (visited);

  for (;;)
    {
      SET_BIT (visited, bb->index);
      if (EDGE_COUNT (bb->succs) == 0
          || TEST_BIT (visited, EDGE_SUCC (bb, 0)->dest->index))
        {
          sbitmap_free (visited);
          return bb;
        }

      bb = EDGE_SUCC (bb, 0)->dest;
    }

  gcc_unreachable ();
}
