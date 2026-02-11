test_state_set_stage (TestState    *state,
                      ClutterActor *stage)
{
  g_assert (!state->was_painted);

  state->stage = stage;
}
