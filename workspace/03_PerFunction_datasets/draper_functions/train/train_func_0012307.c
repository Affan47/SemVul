handle_start_font (GstSamiContext * sctx, const gchar ** atts)
{
  int i;

  sami_context_pop_state (sctx, SPAN_TAG);
  if (atts != NULL) {
    g_string_append (sctx->buf, "<span");
    for (i = 0; (atts[i] != NULL); i += 2) {
      const gchar *key, *value;

      key = atts[i];
      value = atts[i + 1];

      if (!value)
        continue;
      if (!g_ascii_strcasecmp ("color", key)) {


        const gchar *sharp = "";
        int len = strlen (value);

        if (!(*value == '#' && len == 7)) {
          gchar *r;


          if (strtol ((const char *) value, &r, 16) >= 0 &&
              ((gchar *) r == (value + 6) && len == 6)) {
            sharp = "#";
          }
        }


        if (!g_ascii_strcasecmp ("aqua", value)) {
          value = "#00ffff";
        } else if (!g_ascii_strcasecmp ("crimson", value)) {
          value = "#dc143c";
        } else if (!g_ascii_strcasecmp ("fuchsia", value)) {
          value = "#ff00ff";
        } else if (!g_ascii_strcasecmp ("indigo", value)) {
          value = "#4b0082";
        } else if (!g_ascii_strcasecmp ("lime", value)) {
          value = "#00ff00";
        } else if (!g_ascii_strcasecmp ("olive", value)) {
          value = "#808000";
        } else if (!g_ascii_strcasecmp ("silver", value)) {
          value = "#c0c0c0";
        } else if (!g_ascii_strcasecmp ("teal", value)) {
          value = "#008080";
        }
        g_string_append_printf (sctx->buf, " foreground=\"%s%s\"", sharp,
            value);
      } else if (!g_ascii_strcasecmp ("face", key)) {
        g_string_append_printf (sctx->buf, " font_family=\"%s\"", value);
      }
    }
    g_string_append_c (sctx->buf, '>');
    sami_context_push_state (sctx, SPAN_TAG);
  }
}
