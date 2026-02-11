pop_jump (void)
{
  state *new_state = vfr->next_verify_state;
  if (new_state == INVALID_STATE)
    verify_fail ("programmer error in pop_jump");
  if (new_state != NULL)
    {
      vfr->next_verify_state = new_state->next;
      new_state->next = INVALID_STATE;
    }
  return new_state;
}
