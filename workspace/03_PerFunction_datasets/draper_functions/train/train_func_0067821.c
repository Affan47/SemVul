key_pressed_cb (ClutterActor *actor,
                ClutterEvent *event,
                gpointer      user_data)
{
  State *state = (State *) user_data;

  if (!state->transitions_running)
    {
      state->transitions_running = TRUE;
      next_transition_cb (NULL, state);
    }

  return TRUE;
}
