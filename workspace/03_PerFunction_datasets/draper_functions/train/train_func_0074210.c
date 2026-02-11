validate_transports_in_state(or_state_t *state)
{
  int broken = 0;
  config_line_t *line;

  for (line = state->TransportProxies ; line ; line = line->next) {
    tor_assert(!strcmp(line->key, "TransportProxy"));
    if (!state_transport_line_is_valid(line->value))
      broken = 1;
  }

  if (broken)
    log_warn(LD_CONFIG, "state: State file seems to be broken.");

  return 0;
}
