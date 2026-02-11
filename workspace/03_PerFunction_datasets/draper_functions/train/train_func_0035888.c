vect_model_store_cost (stmt_vec_info stmt_info, int ncopies,
		       bool store_lanes_p, enum vect_def_type dt,
		       slp_tree slp_node,
		       stmt_vector_for_cost *prologue_cost_vec,
		       stmt_vector_for_cost *body_cost_vec)
{
  int group_size;
  unsigned int inside_cost = 0, prologue_cost = 0;
  struct data_reference *first_dr;
  gimple first_stmt;


  if (PURE_SLP_STMT (stmt_info))
    return;

  if (dt == vect_constant_def || dt == vect_external_def)
    prologue_cost += record_stmt_cost (prologue_cost_vec, 1, scalar_to_vec,
				       stmt_info, 0, vect_prologue);


  if (STMT_VINFO_GROUPED_ACCESS (stmt_info))
    {
      if (slp_node)
        {
          first_stmt = SLP_TREE_SCALAR_STMTS (slp_node)[0];
          group_size = 1;
        }
      else
        {
          first_stmt = GROUP_FIRST_ELEMENT (stmt_info);
          group_size = vect_cost_group_size (stmt_info);
        }

      first_dr = STMT_VINFO_DATA_REF (vinfo_for_stmt (first_stmt));
    }

  else
    {
      group_size = 1;
      first_dr = STMT_VINFO_DATA_REF (stmt_info);
    }


  if (!store_lanes_p && group_size > 1)
    {


      int nstmts = ncopies * exact_log2 (group_size) * group_size;
      inside_cost = record_stmt_cost (body_cost_vec, nstmts, vec_perm,
				      stmt_info, 0, vect_body);

      if (dump_enabled_p ())
        dump_printf_loc (MSG_NOTE, vect_location,
                         "vect_model_store_cost: strided group_size = %d .",
                         group_size);
    }


  vect_get_store_cost (first_dr, ncopies, &inside_cost, body_cost_vec);

  if (dump_enabled_p ())
    dump_printf_loc (MSG_NOTE, vect_location,
                     "vect_model_store_cost: inside_cost = %d, "
                     "prologue_cost = %d .", inside_cost, prologue_cost);
}
