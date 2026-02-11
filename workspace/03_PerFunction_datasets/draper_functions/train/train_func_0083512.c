yy_token(int tok, yyguts_t* yyg) {
  if (YY_START == PHP_NO_RESERVED_WORDS) {
    pop_state();
  }

  switch (tok) {
    case T_OPEN_TAG:
    case T_OPEN_TAG_WITH_ECHO:
    case T_OPEN_TAG_FAKE:
      push_state(PHP);
      break;

    case T_CLOSE_TAG:
      pop_state();
      return ';';

    case T_OBJECT_OPERATOR:
    case T_PAAMAYIM_NEKUDOTAYIM:
    case T_FUNCTION:
      push_state(PHP_NO_RESERVED_WORDS);
      break;

    case '{':
      yyextra->curly_stack.push(tok);
      break;
  }
#ifdef DEBUG
  yy_log_token(tok);
#endif
  return yyextra->last_token = tok;
}
