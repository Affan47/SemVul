ar_clock_reset (ArClock *clock_widget)
{
  g_return_if_fail (GAMES_IS_CLOCK (clock_widget));

  clock_widget->priv->start_time = clock_widget->priv->stop_time = time (NULL);

  clock_paint (clock_widget);
}
