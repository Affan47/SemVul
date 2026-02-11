button_press_event_cb (ClutterActor *actor,
    ClutterEvent *event,
    ChamplainMarker *marker)
{
  ChamplainMarkerPrivate *priv = marker->priv;
  ClutterButtonEvent *bevent = (ClutterButtonEvent *) event;
  ClutterActor *stage = clutter_actor_get_stage (actor);

  if (event->type != CLUTTER_BUTTON_PRESS ||
      bevent->button != 1 ||
      !stage)
    {
      return FALSE;
    }

  if (priv->draggable)
    {
      if (clutter_actor_transform_stage_point (actor, bevent->x, bevent->y,
              &priv->click_x, &priv->click_y))
        {
          priv->moved = FALSE;
          g_signal_connect (stage,
              "captured-event",
              G_CALLBACK (motion_event_cb),
              marker);

          g_signal_connect (stage,
              "captured-event",
              G_CALLBACK (capture_release_event_cb),
              marker);
        }
    }
  else
    {
      g_signal_connect (marker,
          "button-release-event",
          G_CALLBACK (button_release_event_cb),
          marker);
    }

  if (priv->selectable)
    champlain_marker_set_selected (marker, TRUE);

  if (priv->selectable || priv->draggable)
    {
      ClutterActor *parent;

      parent = clutter_actor_get_parent (CLUTTER_ACTOR (marker));
      clutter_actor_set_child_above_sibling (parent, CLUTTER_ACTOR (marker), NULL);
    }

  g_signal_emit_by_name (marker, "button-press", event);

  return TRUE;
}
