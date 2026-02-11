foo_scroll_area_begin_grab (FooScrollArea *scroll_area,
                            FooScrollAreaEventFunc func,
                            gpointer       input_data)
{
  g_return_if_fail (FOO_IS_SCROLL_AREA (scroll_area));
  g_return_if_fail (!scroll_area->priv->grabbed);

  scroll_area->priv->grabbed = TRUE;
  scroll_area->priv->grab_func = func;
  scroll_area->priv->grab_data = input_data;


}
