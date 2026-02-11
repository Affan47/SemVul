similar_memory_accesses (struct graph *rdg, partition_t partition1,
			 partition_t partition2)
{
  unsigned i, j, k, l;
  bitmap_iterator bi, bj;
  data_reference_p ref1, ref2;


  EXECUTE_IF_AND_IN_BITMAP (partition1->stmts, partition2->stmts, 0, i, bi)
    if (RDG_MEM_WRITE_STMT (rdg, i)
	|| RDG_MEM_READS_STMT (rdg, i))
      return true;


  EXECUTE_IF_SET_IN_BITMAP (partition1->stmts, 0, i, bi)
    if (RDG_MEM_WRITE_STMT (rdg, i)
	|| RDG_MEM_READS_STMT (rdg, i))
      EXECUTE_IF_SET_IN_BITMAP (partition2->stmts, 0, j, bj)
	if (RDG_MEM_WRITE_STMT (rdg, j)
	    || RDG_MEM_READS_STMT (rdg, j))
	  {
	    FOR_EACH_VEC_ELT (RDG_DATAREFS (rdg, i), k, ref1)
	      {
		tree base1 = ref_base_address (ref1);
		if (base1)
		  FOR_EACH_VEC_ELT (RDG_DATAREFS (rdg, j), l, ref2)
		    if (base1 == ref_base_address (ref2))
		      return true;
	      }
	  }

  return false;
}
