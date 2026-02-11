ParseObjectLiteral(bool* ok) {


  Expect(i::Token::LBRACE, CHECK_OK);
  DuplicateFinder duplicate_finder(scanner_->unicode_cache());
  while (peek() != i::Token::RBRACE) {
    i::Token::Value next = peek();
    switch (next) {
      case i::Token::IDENTIFIER:
      case i::Token::FUTURE_RESERVED_WORD:
      case i::Token::FUTURE_STRICT_RESERVED_WORD: {
        bool is_getter = false;
        bool is_setter = false;
        ParseIdentifierNameOrGetOrSet(&is_getter, &is_setter, CHECK_OK);
        if ((is_getter || is_setter) && peek() != i::Token::COLON) {
            i::Token::Value name = Next();
            bool is_keyword = i::Token::IsKeyword(name);
            if (name != i::Token::IDENTIFIER &&
                name != i::Token::FUTURE_RESERVED_WORD &&
                name != i::Token::FUTURE_STRICT_RESERVED_WORD &&
                name != i::Token::NUMBER &&
                name != i::Token::STRING &&
                !is_keyword) {
              *ok = false;
              return Expression::Default();
            }
            if (!is_keyword) {
              LogSymbol();
            }
            PropertyType type = is_getter ? kGetterProperty : kSetterProperty;
            CheckDuplicate(&duplicate_finder, name, type, CHECK_OK);
            ParseFunctionLiteral(CHECK_OK);
            if (peek() != i::Token::RBRACE) {
              Expect(i::Token::COMMA, CHECK_OK);
            }
            continue;
        }
        CheckDuplicate(&duplicate_finder, next, kValueProperty, CHECK_OK);
        break;
      }
      case i::Token::STRING:
        Consume(next);
        CheckDuplicate(&duplicate_finder, next, kValueProperty, CHECK_OK);
        GetStringSymbol();
        break;
      case i::Token::NUMBER:
        Consume(next);
        CheckDuplicate(&duplicate_finder, next, kValueProperty, CHECK_OK);
        break;
      default:
        if (i::Token::IsKeyword(next)) {
          Consume(next);
          CheckDuplicate(&duplicate_finder, next, kValueProperty, CHECK_OK);
        } else {

          *ok = false;
          return Expression::Default();
        }
    }

    Expect(i::Token::COLON, CHECK_OK);
    ParseAssignmentExpression(true, CHECK_OK);


    if (peek() != i::Token::RBRACE) Expect(i::Token::COMMA, CHECK_OK);
  }
  Expect(i::Token::RBRACE, CHECK_OK);

  scope_->NextMaterializedLiteralIndex();
  return Expression::Default();
}
