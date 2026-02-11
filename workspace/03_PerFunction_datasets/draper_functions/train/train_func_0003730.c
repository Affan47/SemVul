elm_config_tooltip_delay_set(double delay)
{
   if (delay < 0.0) return;
   _elm_config->tooltip_delay = delay;
}
