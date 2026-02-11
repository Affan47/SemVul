types_overlap_p (tree empty_type, tree next_type)
{
  struct overlap_info oi;

  if (! IS_AGGR_TYPE (next_type))
    return 0;
  oi.compare_type = next_type;
  oi.found_overlap = 0;
  dfs_walk (TYPE_BINFO (empty_type), dfs_check_overlap,
	    dfs_no_overlap_yet, &oi);
  return oi.found_overlap;
}
