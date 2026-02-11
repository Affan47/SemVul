circuit_establish_circuit(uint8_t purpose, extend_info_t *exit, int flags)
{
  origin_circuit_t *circ;
  int err_reason = 0;

  circ = origin_circuit_init(purpose, flags);

  if (onion_pick_cpath_exit(circ, exit) < 0 ||
      onion_populate_cpath(circ) < 0) {
    circuit_mark_for_close(TO_CIRCUIT(circ), END_CIRC_REASON_NOPATH);
    return NULL;
  }

  control_event_circuit_status(circ, CIRC_EVENT_LAUNCHED, 0);

  if ((err_reason = circuit_handle_first_hop(circ)) < 0) {
    circuit_mark_for_close(TO_CIRCUIT(circ), -err_reason);
    return NULL;
  }
  return circ;
}
