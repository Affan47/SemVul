f90_relop(Token *token, int *multichar)
#else
f90_relop(token, multichar)
     Token *token;
     int *multichar;
#endif
{
  *multichar = FALSE;
  if( curr_char == '>' ) {
    if( next_char == '=' ) {
      token->tsubclass = relop_GE;
      token->src_text = ">=";
      goto twochar_relop;
    }
    else {
      token->tsubclass = relop_GT;
      token->value.string = ">";
      return TRUE;
    }
  }

  if( curr_char == '<' ) {
    if( next_char == '=' ) {
      token->tsubclass = relop_LE;
      token->value.string = "<=";
      goto twochar_relop;
    }
    else {
      token->tsubclass = relop_LT;
      token->value.string = "<";
      return TRUE;
    }
  }

  if( curr_char == '=' && next_char == '=' ) {
      token->tsubclass = relop_EQ;
      token->value.string = "==";
      goto twochar_relop;
  }

  if( curr_char == '/'  && next_char == '=' ) {
      token->tsubclass = relop_NE;
      token->value.string = "/=";
      goto twochar_relop;
  }

  return FALSE;


twochar_relop:
  *multichar = TRUE;
  advance();
  src_text_buf[src_text_len++] = curr_char;
  return TRUE;
}
