move_actors (ClutterActor *actor,
             ClutterEvent *event,
             gpointer      user_data)
{
  State *state = user_data;
  ClutterActor *child;


  if (clutter_timeline_is_playing (clutter_animator_get_timeline (state->animator)))
    return TRUE;


  clutter_animator_remove_key (state->animator, NULL, NULL, -1);


  for (child = clutter_actor_get_first_child (state->group);
       child != NULL;
       child = clutter_actor_get_next_sibling (child))
    {
      add_keys_for_actor (child, state->animator);
    }


  clutter_animator_start (state->animator);

  return TRUE;
}
