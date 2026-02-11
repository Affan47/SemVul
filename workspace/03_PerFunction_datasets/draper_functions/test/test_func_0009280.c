scev_analysis (void)
{
  VEC(gimple,heap) *exit_conditions;

  exit_conditions = VEC_alloc (gimple, heap, 37);
  select_loops_exit_conditions (&exit_conditions);

  if (dump_file && (dump_flags & TDF_STATS))
    analyze_scalar_evolution_for_all_loop_phi_nodes (&exit_conditions);

  number_of_iterations_for_all_loops (&exit_conditions);
  VEC_free (gimple, heap, exit_conditions);
}
