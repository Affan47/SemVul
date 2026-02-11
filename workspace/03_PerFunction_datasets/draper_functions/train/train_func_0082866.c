ctpl_lexer_read_token_data (CtplInputStream *stream,
                            LexerState      *state,
                            GError         **error)
{
  CtplToken  *token   = NULL;
  gchar c;
  gint        prev_c;
  gboolean    escaped = FALSE;
  GString    *gstring;
  GError     *err = NULL;

  (void)state;
  gstring = g_string_new ("");
  while (! err) {
    c = ctpl_input_stream_peek_c (stream, &err);
    if (err || ctpl_input_stream_eof_fast (stream) ||
        ((c == CTPL_START_CHAR || c == CTPL_END_CHAR) && ! escaped)) {
      break;
    } else {
      if (c != CTPL_ESCAPE_CHAR || escaped) {
        g_string_append_c (gstring, c);
      }
      prev_c = ctpl_input_stream_get_c (stream, &err);
      escaped = (prev_c == CTPL_ESCAPE_CHAR) ? ! escaped : FALSE;
    }
  }
  if (! err) {
    c = ctpl_input_stream_peek_c (stream, &err);
  }
  if (err) {
    g_propagate_error (error, err);
  } else {
    if (! (ctpl_input_stream_eof_fast (stream) || c == CTPL_START_CHAR)) {


      ctpl_input_stream_set_error (stream, error, CTPL_LEXER_EXPR_ERROR,
                                   CTPL_LEXER_ERROR_SYNTAX_ERROR,
                                   "Unexpected character '%c' inside data block",
                                   c);
    } else if (gstring->len > 0) {

      token = ctpl_token_new_data (gstring->str, gstring->len);
    }
  }
  g_string_free (gstring, TRUE);

  return token;
}
