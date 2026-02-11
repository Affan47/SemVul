ParseFunctionDeclaration(bool* ok) {


  Expect(Token::FUNCTION, CHECK_OK);
  int function_token_position = scanner().location().beg_pos;
  bool is_reserved = false;
  Handle<String> name = ParseIdentifierOrReservedWord(&is_reserved, CHECK_OK);
  FunctionLiteral* fun = ParseFunctionLiteral(name,
                                              is_reserved,
                                              function_token_position,
                                              DECLARATION,
                                              CHECK_OK);


  Declare(name, Variable::VAR, fun, true, CHECK_OK);
  return EmptyStatement();
}
