fuse_partitions_with_similar_memory_accesses (struct graph *rdg,
					      VEC (bitmap, heap) **partitions)
{
  int p1, p2;
  bitmap partition1, partition2;

  FOR_EACH_VEC_ELT (bitmap, *partitions, p1, partition1)
    if (!can_generate_builtin (rdg, partition1))
      FOR_EACH_VEC_ELT (bitmap, *partitions, p2, partition2)
	if (p1 != p2
	    && !can_generate_builtin (rdg, partition2)
	    && similar_memory_accesses (rdg, partition1, partition2))
	  {
	    bitmap_ior_into (partition1, partition2);
	    VEC_ordered_remove (bitmap, *partitions, p2);
	    p2--;
	  }
}
