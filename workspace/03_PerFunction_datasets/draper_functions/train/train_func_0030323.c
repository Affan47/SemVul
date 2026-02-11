circuit_timeout_want_to_count_circ(origin_circuit_t *circ)
{
  return !circ->has_opened
          && circ->build_state->desired_path_len == DEFAULT_ROUTE_LEN;
}
