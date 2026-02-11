sami_context_init (ParserState * state)
{
  GstSamiContext *context;

  g_assert (state->user_data == NULL);
  state->user_data = (gpointer) g_new0 (GstSamiContext, 1);
  context = (GstSamiContext *) state->user_data;

  context->htmlctxt = htmlCreatePushParserCtxt (samiSAXHandler, context,
      "", 0, NULL, XML_CHAR_ENCODING_UTF8);
  context->buf = g_string_new ("");
  context->rubybuf = g_string_new ("");
  context->resultbuf = g_string_new ("");
  context->state = g_string_new ("");
}
