vect_update_slp_costs_according_to_vf (loop_vec_info loop_vinfo)
{
  unsigned int i, j, vf = LOOP_VINFO_VECT_FACTOR (loop_vinfo);
  vec<slp_instance> slp_instances = LOOP_VINFO_SLP_INSTANCES (loop_vinfo);
  slp_instance instance;
  stmt_vector_for_cost body_cost_vec;
  stmt_info_for_cost *si;
  void *data = LOOP_VINFO_TARGET_COST_DATA (loop_vinfo);

  if (dump_enabled_p ())
    dump_printf_loc (MSG_NOTE, vect_location,
		     "=== vect_update_slp_costs_according_to_vf ===");

  FOR_EACH_VEC_ELT (slp_instances, i, instance)
    {

      int ncopies = vf / SLP_INSTANCE_UNROLLING_FACTOR (instance);


      body_cost_vec = SLP_INSTANCE_BODY_COST_VEC (instance);

      FOR_EACH_VEC_ELT (body_cost_vec, j, si)
	(void) add_stmt_cost (data, si->count * ncopies, si->kind,
			      vinfo_for_stmt (si->stmt), si->misalign,
			      vect_body);
    }
}
