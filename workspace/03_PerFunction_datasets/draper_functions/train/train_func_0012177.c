clutter_keyframe_transition_set_key_frame (ClutterKeyframeTransition *transition,
                                           guint                      index_,
                                           double                     key,
                                           ClutterAnimationMode       mode,
                                           const GValue              *value)
{
  ClutterKeyframeTransitionPrivate *priv;
  KeyFrame *frame;

  g_return_if_fail (CLUTTER_IS_KEYFRAME_TRANSITION (transition));

  priv = transition->priv;
  g_return_if_fail (priv->frames != NULL);
  g_return_if_fail (index_ < priv->frames->len - 1);

  frame = &g_array_index (priv->frames, KeyFrame, index_);
  frame->key = key;
  frame->mode = mode;
  clutter_interval_set_final_value (frame->interval, value);
}
