ctpl_lexer_expr_lex_internal (CtplInputStream  *stream,
                              LexerExprState   *state,
                              GError          **error)
{
  CtplTokenExpr  *expr_tok = NULL;
  GSList         *tokens = NULL;
  GError         *err = NULL;
  gboolean        expect_operand = TRUE;

  if (ctpl_input_stream_skip_blank (stream, error) >= 0) {
    while (! ctpl_input_stream_eof (stream, &err) && ! err) {
      CtplTokenExpr  *token = NULL;
      gchar           c;

      c = ctpl_input_stream_peek_c (stream, &err);
      if (err) {

      } else {
        if (c == ')') {
          if (state->depth <= 0) {
            if (state->lex_all) {

              ctpl_input_stream_set_error (stream, &err, CTPL_LEXER_EXPR_ERROR,
                                           CTPL_LEXER_EXPR_ERROR_SYNTAX_ERROR,
                                           "Too much closing parenthesis");
            }

          } else {
            state->depth --;
            ctpl_input_stream_get_c (stream, &err);
          }

          break;
        } else {
          if (expect_operand) {

            if (c == '(') {
              LexerExprState substate;

              ctpl_input_stream_get_c (stream, &err);
              if (! err) {
                substate = *state;
                substate.depth ++;
                token = ctpl_lexer_expr_lex_internal (stream, &substate, &err);
                if (token && substate.depth != state->depth) {
                  ctpl_input_stream_set_error (stream, &err,
                                               CTPL_LEXER_EXPR_ERROR,
                                               CTPL_LEXER_EXPR_ERROR_SYNTAX_ERROR,
                                               "Missing closing parenthesis");
                }
              }
            } else {
              token = lex_operand (stream, &err);
            }
          } else {

            token = lex_operator (stream, &err);
          }
        }
        if (token) {
          expect_operand = ! expect_operand;
          tokens = g_slist_prepend (tokens, token);
        } else if (! state->lex_all) {
          if (err->domain != CTPL_IO_ERROR) {


            g_clear_error (&err);
          }
          break;
        }

        ctpl_input_stream_skip_blank (stream, &err);
      }
    }
    if (! err) {
      if (! tokens) {

        ctpl_input_stream_set_error (stream, &err, CTPL_LEXER_EXPR_ERROR,
                                     CTPL_LEXER_EXPR_ERROR_FAILED,
                                     "No valid operand at start of expression");
      } else {

        tokens = g_slist_reverse (tokens);
        expr_tok = validate_token_list (stream, tokens, &err);
      }
    }
    if (err) {
      GSList *tmp;

      for (tmp = tokens; tmp; tmp = tmp->next) {


        ctpl_token_expr_free_full (tmp->data, FALSE);
      }
      g_propagate_error (error, err);
    }
    g_slist_free (tokens);
  }

  return expr_tok;
}
