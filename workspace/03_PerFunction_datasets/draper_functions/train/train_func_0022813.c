expr_parse_numeric_factor (void)
{

  switch (expr_parse_lookahead)
    {

    case TOK_LPAREN:
      expr_parse_match (TOK_LPAREN);
      expr_parse_numeric_expr ();
      expr_parse_match (TOK_RPAREN);
      break;

    case TOK_UMINUS:
      expr_parse_match (TOK_UMINUS);
      expr_parse_numeric_factor ();
      expr_eval_action (TOK_UMINUS);
      break;

    case TOK_UPLUS:
      expr_parse_match (TOK_UPLUS);
      expr_parse_numeric_factor ();
      break;

    case TOK_INTEGER:
      expr_eval_action (TOK_INTEGER);
      expr_parse_match (TOK_INTEGER);
      break;

    case TOK_VARIABLE:
      {
        sc_vartype_t token_value, vt_rvalue;
        sc_int type;

        expr_current_token_value (&token_value);
        if (!var_get (expr_varset, token_value.string, &type, &vt_rvalue))
          {
            sc_error ("expr_parse_numeric_factor:"
                      " undefined variable, %s\n", token_value.string);
            longjmp (expr_parse_error, 1);
          }
        if (type != VAR_INTEGER)
          {
            sc_error ("expr_parse_numeric_factor:"
                      " string variable in numeric context, %s\n",
                      token_value.string);
            longjmp (expr_parse_error, 1);
          }
        expr_eval_action (TOK_VARIABLE);
        expr_parse_match (TOK_VARIABLE);
        break;
      }


    case TOK_ABS:

      expr_parse_match (TOK_ABS);
      expr_parse_match (TOK_LPAREN);
      expr_parse_numeric_expr ();
      expr_parse_match (TOK_RPAREN);
      expr_eval_action (TOK_ABS);
      break;

    case TOK_IF:

      expr_parse_match (TOK_IF);
      expr_parse_match (TOK_LPAREN);
      expr_parse_numeric_expr ();
      expr_parse_match (TOK_COMMA);
      expr_parse_numeric_expr ();
      expr_parse_match (TOK_COMMA);
      expr_parse_numeric_expr ();
      expr_parse_match (TOK_RPAREN);
      expr_eval_action (TOK_IF);
      break;

    case TOK_RANDOM:

      expr_parse_match (TOK_RANDOM);
      expr_parse_match (TOK_LPAREN);
      expr_parse_numeric_expr ();
      expr_parse_match (TOK_COMMA);
      expr_parse_numeric_expr ();
      expr_parse_match (TOK_RPAREN);
      expr_eval_action (TOK_RANDOM);
      break;

    case TOK_MAX:
    case TOK_MIN:
    case TOK_EITHER:

      {
        sc_int token, argument_count;


        token = expr_parse_lookahead;
        expr_parse_match (token);
        expr_parse_match (TOK_LPAREN);


        expr_parse_numeric_expr ();
        argument_count = 1;
        while (expr_parse_lookahead == TOK_COMMA)
          {
            expr_parse_match (TOK_COMMA);
            expr_parse_numeric_expr ();
            argument_count++;
          }
        expr_parse_match (TOK_RPAREN);


        expr_eval_push_integer (argument_count);
        expr_eval_action (token);
        break;
      }

    case TOK_INSTR:

      expr_parse_match (TOK_INSTR);
      expr_parse_match (TOK_LPAREN);
      expr_parse_string_expr ();
      expr_parse_match (TOK_COMMA);
      expr_parse_string_expr ();
      expr_parse_match (TOK_RPAREN);
      expr_eval_action (TOK_INSTR);
      break;

    case TOK_LEN:

      expr_parse_match (TOK_LEN);
      expr_parse_match (TOK_LPAREN);
      expr_parse_string_expr ();
      expr_parse_match (TOK_RPAREN);
      expr_eval_action (TOK_LEN);
      break;

    case TOK_VAL:

      expr_parse_match (TOK_VAL);
      expr_parse_match (TOK_LPAREN);
      expr_parse_string_expr ();
      expr_parse_match (TOK_RPAREN);
      expr_eval_action (TOK_VAL);
      break;

    case TOK_IDENT:

      sc_error ("expr_parse_numeric_factor: syntax error, unknown ident\n");
      longjmp (expr_parse_error, 1);

    default:

      sc_error ("expr_parse_numeric_factor:"
                " syntax error, unexpected token, %ld\n", expr_parse_lookahead);
      longjmp (expr_parse_error, 1);
    }
}
