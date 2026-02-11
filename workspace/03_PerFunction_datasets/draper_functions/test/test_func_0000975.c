copy_info_to_removed_store_destinations (int regno)
{
  ira_allocno_t a;
  ira_allocno_t parent_a = NULL;
  ira_loop_tree_node_t parent;
  bool merged_p;

  merged_p = false;
  for (a = ira_regno_allocno_map[regno];
       a != NULL;
       a = ALLOCNO_NEXT_REGNO_ALLOCNO (a))
    {
      if (a != regno_top_level_allocno_map[REGNO (ALLOCNO_REG (a))])

	continue;


      ira_assert (ALLOCNO_CAP_MEMBER (a) == NULL);
      for (parent = ALLOCNO_LOOP_TREE_NODE (a)->parent;
	   parent != NULL;
	   parent = parent->parent)
	if ((parent_a = parent->regno_allocno_map[regno]) == NULL
	    || (parent_a == regno_top_level_allocno_map[REGNO (ALLOCNO_REG
							       (parent_a))]
		&& ALLOCNO_MEM_OPTIMIZED_DEST_P (parent_a)))
	  break;
      if (parent == NULL || parent_a == NULL)
	continue;

      copy_allocno_live_ranges (a, parent_a);
      merge_hard_reg_conflicts (a, parent_a, true);

      ALLOCNO_CALL_FREQ (parent_a) += ALLOCNO_CALL_FREQ (a);
      ALLOCNO_CALLS_CROSSED_NUM (parent_a)
	+= ALLOCNO_CALLS_CROSSED_NUM (a);
      ALLOCNO_EXCESS_PRESSURE_POINTS_NUM (parent_a)
	+= ALLOCNO_EXCESS_PRESSURE_POINTS_NUM (a);
      merged_p = true;
    }
  return merged_p;
}
