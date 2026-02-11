on_timeline_completed (ClutterTimeline  *timeline,
                       ClutterAnimation *animation)
{
  CLUTTER_NOTE (ANIMATION, "Timeline [%p] complete", timeline);

  if (!clutter_animation_get_loop (animation))
    g_signal_emit (animation, animation_signals[COMPLETED], 0);
}
