_clutter_gst_debug_init (void)
{
  const char *env_string;

  env_string = g_getenv ("CLUTTER_GST_DEBUG");

  clutter_gst_timer = g_timer_new ();
  g_timer_start (clutter_gst_timer);

  if (env_string == NULL)
    return TRUE;

  clutter_gst_debug_flags =
    g_parse_debug_string (env_string,
                          clutter_gst_debug_keys,
                          G_N_ELEMENTS (clutter_gst_debug_keys));

  return TRUE;
}
