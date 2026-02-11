cally_actor_action_do_action (AtkAction *action,
                             gint       index)
{
  CallyActor           *cally_actor = NULL;
  AtkStateSet          *set         = NULL;
  CallyActorPrivate    *priv        = NULL;
  CallyActorActionInfo *info        = NULL;

  cally_actor = CALLY_ACTOR (action);
  priv = cally_actor->priv;

  set = atk_object_ref_state_set (ATK_OBJECT (cally_actor));

  if (atk_state_set_contains_state (set, ATK_STATE_DEFUNCT))
    return FALSE;

  if (!atk_state_set_contains_state (set, ATK_STATE_SENSITIVE) ||
      !atk_state_set_contains_state (set, ATK_STATE_SHOWING))
    return FALSE;

  g_object_unref (set);

  info = _cally_actor_get_action_info (cally_actor, index);

  if (info == NULL)
    return FALSE;

  if (info->do_action_func == NULL)
    return FALSE;

  if (!priv->action_queue)
    priv->action_queue = g_queue_new ();

  g_queue_push_head (priv->action_queue, info);

  if (!priv->action_idle_handler)
    priv->action_idle_handler = g_idle_add (idle_do_action, cally_actor);

  return TRUE;
}
