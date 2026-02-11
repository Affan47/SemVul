write_state(const State& state)
{
  int i;

  for (i = 0; i <= 0x18; i++) {
    write(i, state.sid_register[i]);
  }

  bus_value = state.bus_value;
  bus_value_ttl = state.bus_value_ttl;

  for (i = 0; i < 3; i++) {
    voice[i].wave.accumulator = state.accumulator[i];
    voice[i].wave.shift_register = state.shift_register[i];
    voice[i].envelope.rate_counter = state.rate_counter[i];
    voice[i].envelope.rate_period = state.rate_counter_period[i];
    voice[i].envelope.exponential_counter = state.exponential_counter[i];
    voice[i].envelope.exponential_counter_period = state.exponential_counter_period[i];
    voice[i].envelope.envelope_counter = state.envelope_counter[i];
    voice[i].envelope.state = state.envelope_state[i];
    voice[i].envelope.hold_zero = state.hold_zero[i];
  }
}
