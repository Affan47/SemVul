circuit_append_new_exit(origin_circuit_t *circ, extend_info_t *exit)
{
  cpath_build_state_t *state;
  tor_assert(exit);
  tor_assert(circ);

  state = circ->build_state;
  tor_assert(state);
  extend_info_free(state->chosen_exit);
  state->chosen_exit = extend_info_dup(exit);

  ++circ->build_state->desired_path_len;
  onion_append_hop(&circ->cpath, exit);
  return 0;
}
