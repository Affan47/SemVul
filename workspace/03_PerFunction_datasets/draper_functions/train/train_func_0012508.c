expand_omp_atomic (struct omp_region *region)
{
  basic_block load_bb = region->entry, store_bb = region->exit;
  gimple load = last_stmt (load_bb), store = last_stmt (store_bb);
  tree loaded_val = gimple_omp_atomic_load_lhs (load);
  tree addr = gimple_omp_atomic_load_rhs (load);
  tree stored_val = gimple_omp_atomic_store_val (store);
  tree type = TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (addr)));
  HOST_WIDE_INT index;


  index = tree_low_cst (TYPE_SIZE_UNIT (type), 1);
  index = exact_log2 (index);
  if (index >= 0 && index <= 4)
    {
      unsigned int align = TYPE_ALIGN_UNIT (type);


      if (exact_log2 (align) >= index)
	{

	  if ((INTEGRAL_TYPE_P (type) || POINTER_TYPE_P (type))
	      && store_bb == single_succ (load_bb))
	    {
	      if (expand_omp_atomic_fetch_op (load_bb, addr,
					      loaded_val, stored_val, index))
		return;
	    }


	  if (expand_omp_atomic_pipeline (load_bb, store_bb, addr,
					  loaded_val, stored_val, index))
	    return;
	}
    }


  expand_omp_atomic_mutex (load_bb, store_bb, addr, loaded_val, stored_val);
}
