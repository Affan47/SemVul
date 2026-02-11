are_reqs_active(const struct player *target_player,
		     const struct city *target_city,
		     const struct impr_type *target_building,
		     const struct tile *target_tile,
		     const struct unit_type *target_unittype,
		     const struct output_type *target_output,
		     const struct specialist *target_specialist,
		     const struct requirement_vector *reqs,
                     const enum   req_problem_type prob_type)
{
  requirement_vector_iterate(reqs, preq) {
    if (!is_req_active(target_player, target_city, target_building,
		       target_tile, target_unittype, target_output,
		       target_specialist,
		       preq, prob_type)) {
      return FALSE;
    }
  } requirement_vector_iterate_end;
  return TRUE;
}
