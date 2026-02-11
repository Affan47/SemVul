waterfall_set_max_size (Waterfall *waterfall,
                        gdouble max_size)
{
  if (max_size == waterfall->max_size)
    return;

  waterfall->max_size = max_size;

  queue_redraw (waterfall);
}
