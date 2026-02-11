clamp_adjustment (MxKineticScrollView *scroll,
                  MxAdjustment        *adj,
                  guint                duration)
{
  MxKineticScrollViewPrivate *priv = scroll->priv;
  gdouble d, value, lower, upper, step_increment, page_size;


  mx_adjustment_get_values (adj, &value, &lower, &upper,
                            &step_increment, NULL, &page_size);

  d = (rint ((value - lower) / step_increment) *
      step_increment) + lower;

  if (priv->clamp_to_center)
    {
      gdouble offset = page_size / 2;
      offset -= step_increment / 2;
      offset = step_increment - (int) offset % (int) step_increment;

      if (offset > step_increment / 2)
        offset = - (step_increment - offset);

      d += offset;
    }

  if (mx_adjustment_get_clamp_value (adj))
    d = CLAMP (d, lower, upper - page_size);

  g_signal_connect (adj, "interpolation-completed",
                    G_CALLBACK (interpolation_completed_cb), scroll);
  mx_adjustment_interpolate (adj, d, duration, priv->clamp_mode);
}
