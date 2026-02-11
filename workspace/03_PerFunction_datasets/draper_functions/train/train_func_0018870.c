circuit_dump_details(int severity, circuit_t *circ, int conn_array_index,
                     const char *type, int this_circid, int other_circid)
{
  log(severity, LD_CIRC, "Conn %d has %s circuit: circID %d (other side %d), "
      "state %d (%s), born %ld:",
      conn_array_index, type, this_circid, other_circid, circ->state,
      circuit_state_to_string(circ->state),
      (long)circ->timestamp_created.tv_sec);
  if (CIRCUIT_IS_ORIGIN(circ)) {
    circuit_log_path(severity, LD_CIRC, TO_ORIGIN_CIRCUIT(circ));
  }
}
