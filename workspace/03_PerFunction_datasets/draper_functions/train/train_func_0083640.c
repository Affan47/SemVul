clutter_interval_set_initial_value (ClutterInterval *interval,
                                    const GValue    *value)
{
  g_return_if_fail (CLUTTER_IS_INTERVAL (interval));
  g_return_if_fail (value != NULL);

  clutter_interval_set_value_internal (interval, INITIAL, value);
}
