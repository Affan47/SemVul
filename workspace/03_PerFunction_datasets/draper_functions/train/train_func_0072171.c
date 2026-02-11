on_handle_capture_event (ClutterActor *trough,
                         ClutterEvent *event,
                         MxSlider     *bar)
{
  MxSliderPrivate *priv = bar->priv;

  if (clutter_event_type (event) == CLUTTER_MOTION)
    {
      drag_handle (bar,
                   ((ClutterMotionEvent*)event)->x,
                   ((ClutterMotionEvent*)event)->y);
    }
  else if (clutter_event_type (event) == CLUTTER_BUTTON_RELEASE
           && ((ClutterButtonEvent*)event)->button == 1)
    {
      ClutterActor *stage, *target;

      stage = clutter_actor_get_stage(priv->trough);

      if (priv->capture_handler)
        {
          g_signal_handler_disconnect (stage, priv->capture_handler);
          priv->capture_handler = 0;


          mx_slider_allocate_fill_handle (bar, NULL, 0);
          clutter_actor_queue_redraw (CLUTTER_ACTOR (bar));
        }

      clutter_set_motion_events_enabled (TRUE);


      target =
        clutter_stage_get_actor_at_pos ((ClutterStage*) stage,
                                        CLUTTER_PICK_REACTIVE,
                                        ((ClutterButtonEvent*) event)->x,
                                        ((ClutterButtonEvent*) event)->y);
      if (target != priv->handle)
        {
          mx_stylable_set_style_pseudo_class (MX_STYLABLE (priv->handle),
                                            NULL);
        }
    }

  return FALSE;
}
