rule_factor () {
  Node  *out = NULL;
  Value *val = NULL;

  if (yycc == NUMBER) {
    val = Value_int (atoi (yytext));
    next_token ();
    return Node_new (N_INT_EXP, val, NULL, NULL);

  } else if (yycc == VAR_ID) {
    out = rule_variable ();

  } else if (yycc == FUN_ID) {
    out = rule_funCallExp ();

  } else if (yycc == '(') {
    next_token ();
    out = rule_expression ();

    if (yycc == ')') {
      next_token ();

    } else expecting ("')'");

  } else if (yycc == READ) {
    next_token ();

    if (yycc == '(') {
      next_token ();

      if (yycc == ')') {
        next_token ();

      } else expecting ("')'");
    } else expecting ("'('");
    return Node_new (N_READ_EXP, NULL, NULL, NULL);

  } else expecting ("factor");

  return out;
}
