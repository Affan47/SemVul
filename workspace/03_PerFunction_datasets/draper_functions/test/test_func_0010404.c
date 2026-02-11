vect_model_induction_cost (stmt_vec_info stmt_info, int ncopies)
{
  loop_vec_info loop_vinfo = STMT_VINFO_LOOP_VINFO (stmt_info);
  void *target_cost_data = LOOP_VINFO_TARGET_COST_DATA (loop_vinfo);
  unsigned inside_cost, prologue_cost;


  inside_cost = add_stmt_cost (target_cost_data, ncopies, vector_stmt,
			       stmt_info, 0, vect_body);


  prologue_cost = add_stmt_cost (target_cost_data, 2, scalar_to_vec,
				 stmt_info, 0, vect_prologue);

  if (dump_enabled_p ())
    dump_printf_loc (MSG_NOTE, vect_location,
                     "vect_model_induction_cost: inside_cost = %d, "
                     "prologue_cost = %d .", inside_cost, prologue_cost);
}
