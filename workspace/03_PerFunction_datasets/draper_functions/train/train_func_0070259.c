test_state_free (TestState *state)
{
  if (state->id != 0)
    g_source_remove (state->id);

  if (state->actors != NULL)
    g_ptr_array_unref (state->actors);

  if (state->colors != NULL)
    g_ptr_array_unref (state->colors);

  if (state->stage != NULL)
    clutter_actor_destroy (state->stage);

  g_slice_free (TestState, state);
}
