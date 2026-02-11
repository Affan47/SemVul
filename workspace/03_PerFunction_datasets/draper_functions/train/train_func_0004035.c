parser_state_dispose (GstSubParse * self, ParserState * state)
{
  if (state->buf) {
    g_string_free (state->buf, TRUE);
    state->buf = NULL;
  }
  if (state->user_data) {
    switch (self->parser_type) {
#ifndef GST_DISABLE_XML
      case GST_SUB_PARSE_FORMAT_SAMI:
        sami_context_reset (state);
        break;
#endif
      default:
        break;
    }
  }
}
