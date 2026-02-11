ParseDebuggerStatement(bool* ok) {


  Expect(i::Token::DEBUGGER, CHECK_OK);
  ExpectSemicolon(ok);
  return Statement::Default();
}
