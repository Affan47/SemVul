unsigned_dec (const char **typep)
{
  token tok;

  peek (&tok);
  switch (tok.kind)
    {
    case TOK_CHAR:
      get_token (&tok);
      *typep = "u_char";
      break;
    case TOK_SHORT:
      get_token (&tok);
      *typep = "u_short";
      (void) peekscan (TOK_INT, &tok);
      break;
    case TOK_LONG:
      get_token (&tok);
      *typep = "u_long";
      (void) peekscan (TOK_INT, &tok);
      break;
    case TOK_HYPER:
      get_token (&tok);
      *typep = "u_quad_t";
      (void) peekscan(TOK_INT, &tok);
      break;
    case TOK_INT:
      get_token (&tok);
      *typep = "u_int";
      break;
    default:
      *typep = "u_int";
      break;
    }
}
