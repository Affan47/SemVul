set_zoom_percent(guint percent)
{
  if(percent == 0)
    return;

  const double scale = (double)percent / 100;
  if(scale == 0)
    return;

  set_scale(scale);
}
