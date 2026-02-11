st_scroll_view_get_column_size (StScrollView *scroll)
{
  gdouble column_size;

  g_return_val_if_fail (scroll, 0);

  g_object_get (scroll->priv->hadjustment,
                "step-increment", &column_size,
                NULL);

  return column_size;
}
