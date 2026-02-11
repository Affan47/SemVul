free_state (state_t state)
{
  free_alt_states (state->component_states);
  VLA_PTR_ADD (free_states, state);
}
