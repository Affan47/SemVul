cally_actor_get_n_children (AtkObject *obj)
{
  ClutterActor *actor = NULL;

  g_return_val_if_fail (CALLY_IS_ACTOR (obj), 0);

  actor = CALLY_GET_CLUTTER_ACTOR (obj);

  if (actor == NULL)
    return 0;

  g_return_val_if_fail (CLUTTER_IS_ACTOR (actor), 0);

  return clutter_actor_get_n_children (actor);
}
