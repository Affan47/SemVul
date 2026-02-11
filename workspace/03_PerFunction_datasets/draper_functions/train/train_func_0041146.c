tmplayer_parse_line (ParserState * state, const gchar * line, guint line_num)
{
  GstClockTime ts = GST_CLOCK_TIME_NONE;
  const gchar *text_start = NULL;
  gchar *ret = NULL;
  gchar divc = '\0';
  guint h, m, s, l = 1;

  if (sscanf (line, "%u:%02u:%02u,%u%c", &h, &m, &s, &l, &divc) == 5 &&
      (divc == '=')) {
    GST_LOG ("multiline format %u %u %u %u", h, m, s, l);
    ts = GST_SECOND * ((((h * 60) + m) * 60) + s);
    text_start = strchr (line, '=');
  } else if (sscanf (line, "%u:%02u:%02u%c", &h, &m, &s, &divc) == 4 &&
      (divc == '=' || divc == ':')) {
    GST_LOG ("single line format %u %u %u %u %c", h, m, s, l, divc);
    ts = GST_SECOND * ((((h * 60) + m) * 60) + s);
    text_start = strchr (line + 6, divc);
  } else if (line[0] == '\0' && state->buf->len > 0 &&
      GST_CLOCK_TIME_IS_VALID (state->start_time)) {


    GST_LOG ("empty line, and there's still text in the buffer");
    ret = tmplayer_process_buffer (state);
    state->duration = GST_CLOCK_TIME_NONE;
    return ret;
  } else {
    GST_WARNING ("failed to parse line: '%s'", line);
    return NULL;
  }


  if (text_start == NULL || text_start[1] == '\0' ||
      (l == 1 && state->buf->len > 0)) {

    if (GST_CLOCK_TIME_IS_VALID (state->start_time) &&
        state->start_time < ts && line_num > 0) {
      ret = tmplayer_process_buffer (state);
      state->duration = ts - state->start_time;


      g_string_append (state->buf, text_start + 1);
    } else if (line_num > 0) {
      GST_WARNING ("end of subtitle unit but no valid start time?!");
    }
  } else {
    if (l > 1)
      g_string_append_c (state->buf, '\n');
    g_string_append (state->buf, text_start + 1);
    state->start_time = ts;
  }

  GST_LOG ("returning: '%s'", GST_STR_NULL (ret));
  return ret;
}
