_mx_scroll_view_ensure_visible_axis (MxScrollBar  *bar,
                                     gdouble       lower,
                                     gdouble       upper)
{
  gdouble new_value, adjust_lower, adjust_upper, adjust_page_size;

  gboolean changed = FALSE;
  MxAdjustment *adjust = mx_scroll_bar_get_adjustment (bar);

  mx_adjustment_get_values (adjust,
                            &new_value,
                            &adjust_lower,
                            &adjust_upper,
                            NULL,
                            NULL,
                            &adjust_page_size);


  lower = CLAMP (lower, adjust_lower, adjust_upper - adjust_page_size);
  upper = CLAMP (upper, adjust_lower + adjust_page_size, adjust_upper);


  if (new_value + adjust_page_size < upper)
    {
      new_value = upper - adjust_page_size;
      changed = TRUE;
    }


  if (lower < new_value)
    {
      new_value = lower;
      changed = TRUE;
    }

  if (changed)
    mx_adjustment_interpolate (adjust, new_value,
                               250, CLUTTER_EASE_OUT_CUBIC);
}
