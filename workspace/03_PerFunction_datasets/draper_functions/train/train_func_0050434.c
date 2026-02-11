gst_debug_construct_term_color (guint colorinfo)
{
  GString *color;

  color = g_string_new ("\033[00");

  if (colorinfo & GST_DEBUG_BOLD) {
    g_string_append_len (color, ";01", 3);
  }
  if (colorinfo & GST_DEBUG_UNDERLINE) {
    g_string_append_len (color, ";04", 3);
  }
  if (colorinfo & GST_DEBUG_FG_MASK) {
    g_string_append_printf (color, ";3%1d", colorinfo & GST_DEBUG_FG_MASK);
  }
  if (colorinfo & GST_DEBUG_BG_MASK) {
    g_string_append_printf (color, ";4%1d",
        (colorinfo & GST_DEBUG_BG_MASK) >> 4);
  }
  g_string_append_c (color, 'm');

  return g_string_free (color, FALSE);
}
