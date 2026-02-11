rdg_flag_uses (struct graph *rdg, int u, bitmap partition, bitmap loops,
	       bitmap processed, bool *part_has_writes)
{
  use_operand_p use_p;
  struct vertex *x = &(rdg->vertices[u]);
  gimple stmt = RDGV_STMT (x);
  struct graph_edge *anti_dep = has_anti_dependence (x);


  if (anti_dep)
    {
      int v = anti_dep->dest;

      if (!already_processed_vertex_p (processed, v))
	rdg_flag_vertex_and_dependent (rdg, v, partition, loops,
				       processed, part_has_writes);
    }

  if (gimple_code (stmt) != GIMPLE_PHI)
    {
      if ((use_p = gimple_vuse_op (stmt)) != NULL_USE_OPERAND_P)
	{
	  tree use = USE_FROM_PTR (use_p);

	  if (TREE_CODE (use) == SSA_NAME)
	    {
	      gimple def_stmt = SSA_NAME_DEF_STMT (use);
	      int v = rdg_vertex_for_stmt (rdg, def_stmt);

	      if (v >= 0
		  && !already_processed_vertex_p (processed, v))
		rdg_flag_vertex_and_dependent (rdg, v, partition, loops,
					       processed, part_has_writes);
	    }
	}
    }

  if (is_gimple_assign (stmt) && has_upstream_mem_writes (u))
    {
      tree op0 = gimple_assign_lhs (stmt);


      if (is_gimple_reg (op0))
	{
	  use_operand_p use_p;
	  imm_use_iterator iter;

	  FOR_EACH_IMM_USE_FAST (use_p, iter, op0)
	    {
	      int v = rdg_vertex_for_stmt (rdg, USE_STMT (use_p));

	      if (!already_processed_vertex_p (processed, v))
		rdg_flag_vertex_and_dependent (rdg, v, partition, loops,
					       processed, part_has_writes);
	    }
	}
    }
}
