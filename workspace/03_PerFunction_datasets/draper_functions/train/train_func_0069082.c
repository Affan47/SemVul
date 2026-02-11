vect_model_simple_cost (stmt_vec_info stmt_info, int ncopies,
			enum vect_def_type *dt, slp_tree slp_node)
{
  int i;
  int inside_cost = 0, outside_cost = 0;


  if (PURE_SLP_STMT (stmt_info))
    return;

  inside_cost = ncopies * vect_get_stmt_cost (vector_stmt);


  for (i = 0; i < 2; i++)
    {
      if (dt[i] == vect_constant_def || dt[i] == vect_external_def)
	outside_cost += vect_get_stmt_cost (vector_stmt);
    }

  if (vect_print_dump_info (REPORT_COST))
    fprintf (vect_dump, "vect_model_simple_cost: inside_cost = %d, "
             "outside_cost = %d .", inside_cost, outside_cost);


  stmt_vinfo_set_inside_of_loop_cost (stmt_info, slp_node, inside_cost);
  stmt_vinfo_set_outside_of_loop_cost (stmt_info, slp_node, outside_cost);
}
