cally_actor_grab_focus (AtkComponent    *component)
{
  ClutterActor *actor      = NULL;
  ClutterActor *stage      = NULL;
  CallyActor    *cally_actor = NULL;

  g_return_val_if_fail (CALLY_IS_ACTOR (component), FALSE);


  cally_actor = CALLY_ACTOR(component);
  actor = CALLY_GET_CLUTTER_ACTOR (cally_actor);
  stage = clutter_actor_get_stage (actor);

  clutter_stage_set_key_focus (CLUTTER_STAGE (stage),
                               actor);

  return TRUE;
}
