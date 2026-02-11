_clutter_actor_traverse_depth (ClutterActor           *actor,
                               ClutterTraverseCallback before_children_callback,
                               ClutterTraverseCallback after_children_callback,
                               int                     current_depth,
                               gpointer                user_data)
{
  ClutterActorTraverseVisitFlags flags;

  flags = before_children_callback (actor, current_depth, user_data);
  if (flags & CLUTTER_ACTOR_TRAVERSE_VISIT_BREAK)
    return CLUTTER_ACTOR_TRAVERSE_VISIT_BREAK;

  if (!(flags & CLUTTER_ACTOR_TRAVERSE_VISIT_SKIP_CHILDREN))
    {
      ClutterActor *iter;

      for (iter = actor->priv->first_child;
           iter != NULL;
           iter = iter->priv->next_sibling)
        {
          flags = _clutter_actor_traverse_depth (iter,
                                                 before_children_callback,
                                                 after_children_callback,
                                                 current_depth + 1,
                                                 user_data);

          if (flags & CLUTTER_ACTOR_TRAVERSE_VISIT_BREAK)
            return CLUTTER_ACTOR_TRAVERSE_VISIT_BREAK;
        }
    }

  if (after_children_callback)
    return after_children_callback (actor, current_depth, user_data);
  else
    return CLUTTER_ACTOR_TRAVERSE_VISIT_CONTINUE;
}
