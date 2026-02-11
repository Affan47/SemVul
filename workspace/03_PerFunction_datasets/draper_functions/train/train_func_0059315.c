validate_state (gpointer data)
{
  TestState *state = data;
  int i;


  if (test_state_in_validation (state))
    return G_SOURCE_REMOVE;

  g_assert (state->actors != NULL);
  g_assert (state->colors != NULL);

  g_assert_cmpint (state->actors->len, ==, state->colors->len);

  test_state_push_validation (state);

  if (g_test_verbose ())
    g_print ("Sampling %d actors\n", state->actors->len);

  for (i = 0; i < state->actors->len; i++)
    {
      ClutterActor *actor = g_ptr_array_index (state->actors, i);
      ClutterColor *color = g_ptr_array_index (state->colors, i);
      ClutterActorBox box;

      clutter_actor_get_allocation_box (actor, &box);

      check_color_at (state->stage, actor, color, box.x1 + 2, box.y1 + 2);
      check_color_at (state->stage, actor, color, box.x2 - 2, box.y2 - 2);
    }

  test_state_pop_validation (state);

  state->was_painted = TRUE;

  return G_SOURCE_REMOVE;
}
