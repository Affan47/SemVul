blocks_nreverse_all (tree t)
{
  tree prev = 0, block, next;
  for (block = t; block; block = next)
    {
      next = BLOCK_CHAIN (block);
      BLOCK_CHAIN (block) = prev;
      if (BLOCK_FRAGMENT_CHAIN (block)
	  && BLOCK_FRAGMENT_ORIGIN (block) == NULL_TREE)
	{
	  BLOCK_FRAGMENT_CHAIN (block)
	    = block_fragments_nreverse (BLOCK_FRAGMENT_CHAIN (block));
	  if (!BLOCK_SAME_RANGE (BLOCK_FRAGMENT_CHAIN (block)))
	    BLOCK_SAME_RANGE (block) = 0;
	}
      BLOCK_SUBBLOCKS (block) = blocks_nreverse_all (BLOCK_SUBBLOCKS (block));
      prev = block;
    }
  return prev;
}
