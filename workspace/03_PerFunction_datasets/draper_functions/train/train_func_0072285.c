lexFloatingPointLiteral(Cursor Range, Cursor C, MIToken &Token) {
  C.advance();

  while (isdigit(C.peek()))
    C.advance();
  if ((C.peek() == 'e' || C.peek() == 'E') &&
      (isdigit(C.peek(1)) ||
       ((C.peek(1) == '-' || C.peek(1) == '+') && isdigit(C.peek(2))))) {
    C.advance(2);
    while (isdigit(C.peek()))
      C.advance();
  }
  Token.reset(MIToken::FloatingPointLiteral, Range.upto(C));
  return C;
}
