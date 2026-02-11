expr_current_token_value (sc_vartype_t *value)
{

  switch (expr_current_token)
    {
    case TOK_INTEGER:
    case TOK_STRING:
    case TOK_VARIABLE:
    case TOK_IDENT:
      break;

    default:
      sc_fatal ("expr_current_token_value:"
                " taking undefined token value, %ld\n", expr_current_token);
    }


  *value = expr_token_value;
}
