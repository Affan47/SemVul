ParseVariableDeclarations(bool accept_IN,
                                                          int* num_decl,
                                                          bool* ok) {


  if (peek() == i::Token::VAR) {
    Consume(i::Token::VAR);
  } else if (peek() == i::Token::CONST) {
    Consume(i::Token::CONST);
  } else {
    *ok = false;
    return 0;
  }


  int nvars = 0;
  do {

    if (nvars > 0) Consume(i::Token::COMMA);
    ParseIdentifier(CHECK_OK);
    nvars++;
    if (peek() == i::Token::ASSIGN) {
      Expect(i::Token::ASSIGN, CHECK_OK);
      ParseAssignmentExpression(accept_IN, CHECK_OK);
    }
  } while (peek() == i::Token::COMMA);

  if (num_decl != NULL) *num_decl = nvars;
  return kUnknownStatement;
}
