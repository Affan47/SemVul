rule_returnInstruction () {
  Node *expr = NULL;

  if (yycc == RETURN) {
    next_token ();

    if (yycc == '(' || yycc == NUMBER || yycc == VAR_ID ||
        yycc == READ || yycc == FUN_ID) {
      expr = rule_expression ();

      if (yycc == ';') {
        next_token ();

      } else expecting ("';'");
    } else expecting ("expression");
  } else expecting ("keyword RETURN");

  return Node_new (N_RETURN_INST, NULL, NULL, expr);
}
