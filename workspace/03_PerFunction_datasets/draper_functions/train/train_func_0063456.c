parse_sami (ParserState * state, const gchar * line)
{
  gchar *ret = NULL;
  GstSamiContext *context = (GstSamiContext *) state->user_data;

  gchar *unescaped = unescape_string (line);
  html_context_parse (context->htmlctxt, (gchar *) unescaped,
      strlen (unescaped));
  g_free (unescaped);

  if (context->has_result) {
    if (context->rubybuf->len) {
      context->rubybuf = g_string_append_c (context->rubybuf, '\n');
      g_string_prepend (context->resultbuf, context->rubybuf->str);
      context->rubybuf = g_string_truncate (context->rubybuf, 0);
    }

    ret = g_string_free (context->resultbuf, FALSE);
    context->resultbuf = g_string_new ("");
    state->start_time = context->time1;
    state->duration = context->time2 - context->time1;
    context->has_result = FALSE;
  }
  return ret;
}
