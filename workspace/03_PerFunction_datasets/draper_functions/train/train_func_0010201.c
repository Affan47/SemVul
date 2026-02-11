clutter_keyframe_transition_update_frames (ClutterKeyframeTransition *transition)
{
  ClutterKeyframeTransitionPrivate *priv = transition->priv;
  guint i;

  if (priv->frames == NULL)
    return;

  for (i = 0; i < priv->frames->len; i++)
    {
      KeyFrame *cur_frame = &g_array_index (priv->frames, KeyFrame, i);
      KeyFrame *prev_frame;

      if (i > 0)
        prev_frame = &g_array_index (priv->frames, KeyFrame, i - 1);
      else
        prev_frame = NULL;

      if (prev_frame != NULL)
        {
          cur_frame->start = prev_frame->key;

          if (prev_frame->interval != NULL)
            {
              const GValue *value;

              value = clutter_interval_peek_final_value (prev_frame->interval);

              if (cur_frame->interval != NULL)
                clutter_interval_set_initial_value (cur_frame->interval, value);
              else
                {
                  cur_frame->interval =
                    clutter_interval_new_with_values (G_VALUE_TYPE (value), value, NULL);
                }
            }
        }
      else
        cur_frame->start = 0.0;

      cur_frame->end = cur_frame->key;
    }
}
