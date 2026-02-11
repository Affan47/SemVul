unrealize_actor_before_children_cb (ClutterActor *self,
                                    int depth,
                                    void *user_data)
{


  if (!CLUTTER_ACTOR_IS_REALIZED (self))
    return CLUTTER_ACTOR_TRAVERSE_VISIT_SKIP_CHILDREN;

  g_signal_emit (self, actor_signals[UNREALIZE], 0);

  return CLUTTER_ACTOR_TRAVERSE_VISIT_CONTINUE;
}
