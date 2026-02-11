sami_context_reset (ParserState * state)
{
  GstSamiContext *context = (GstSamiContext *) state->user_data;

  if (context) {
    g_string_truncate (context->buf, 0);
    g_string_truncate (context->rubybuf, 0);
    g_string_truncate (context->resultbuf, 0);
    g_string_truncate (context->state, 0);
    context->has_result = FALSE;
    context->in_sync = FALSE;
    context->time1 = 0;
    context->time2 = 0;
  }
}
