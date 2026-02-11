read_tree_node (unsigned int blockNr, int depth)
{
  char* cache = CACHE(depth);
  int num_cached = INFO->cached_slots;
  if (depth < num_cached)
    {


      if (blockNr == INFO->blocks[depth])
	return cache;
    }
  else
    cache = CACHE(num_cached);

#ifdef REISERDEBUG
  printf ("  next read_in: block=%d (depth=%d)\n",
	  blockNr, depth);
#endif
  if (! block_read (blockNr, 0, INFO->blocksize, cache))
    return 0;

  if (BLOCKHEAD (cache)->blk_level != depth)
    {
      errnum = ERR_FSYS_CORRUPT;
      return 0;
    }

  INFO->blocks[depth] = blockNr;
  return cache;
}
