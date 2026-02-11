clutter_snap_constraint_set_edges (ClutterSnapConstraint *constraint,
                                   ClutterSnapEdge        from_edge,
                                   ClutterSnapEdge        to_edge)
{
  gboolean from_changed = FALSE, to_changed = FALSE;

  g_return_if_fail (CLUTTER_IS_SNAP_CONSTRAINT (constraint));

  g_object_freeze_notify (G_OBJECT (constraint));

  if (constraint->from_edge != from_edge)
    {
      constraint->from_edge = from_edge;
      g_object_notify_by_pspec (G_OBJECT (constraint),
                                obj_props[PROP_FROM_EDGE]);
      from_changed = TRUE;
    }

  if (constraint->to_edge != to_edge)
    {
      constraint->to_edge = to_edge;
      g_object_notify_by_pspec (G_OBJECT (constraint),
                                obj_props[PROP_TO_EDGE]);
      to_changed = TRUE;
    }

  if ((from_changed || to_changed) &&
      constraint->actor != NULL)
    {
      clutter_actor_queue_relayout (constraint->actor);
    }

  g_object_thaw_notify (G_OBJECT (constraint));
}
