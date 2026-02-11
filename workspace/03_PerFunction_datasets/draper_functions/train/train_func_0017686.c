rule_variable () {
  Node  *index = NULL;
  Value *name  = NULL;

  if (yycc == VAR_ID) {
    name = Value_str (yytext);
    next_token ();

    if (yycc == '[') {
      next_token ();
      index = rule_expression ();

      if (yycc == ']') {
        next_token ();
      } else expecting ("']'");
    }

  } else expecting ("variable identifier");

  return Node_new (N_VAR, name, NULL, index);
}
