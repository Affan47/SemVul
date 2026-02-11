cm_find_best_solution(struct cm_state *state,
                                  const struct cm_parameter *const parameter,
                                  struct cm_result *result)
{
  int loop_count = 0;
  int max_count;
  struct city backup;

#ifdef GATHER_TIME_STATS
  performance.current = &performance.opt;
#endif

  begin_search(state, parameter);


  memcpy(&backup, state->pcity, sizeof(backup));

  if (player_is_cpuhog(city_owner(state->pcity))) {
    max_count = CPUHOG_CM_MAX_LOOP;
  } else {
    max_count = CM_MAX_LOOP;
  }


  while (!bb_next(state)) {

    loop_count++;

    if (loop_count > max_count) {
      log_error("Did not find a cm solution in %d iterations for %s.",
                max_count, city_name(state->pcity));
      break;
    }
  }


  convert_solution_to_result(state, &state->best, result);

  memcpy(state->pcity, &backup, sizeof(backup));

  end_search(state);
}
