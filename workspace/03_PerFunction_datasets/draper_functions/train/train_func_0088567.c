maybeLexSymbol(Cursor C, MIToken &Token) {
  MIToken::TokenKind Kind;
  unsigned Length = 1;
  if (C.peek() == ':' && C.peek(1) == ':') {
    Kind = MIToken::coloncolon;
    Length = 2;
  } else
    Kind = symbolToken(C.peek());
  if (Kind == MIToken::Error)
    return None;
  auto Range = C;
  C.advance(Length);
  Token.reset(Kind, Range.upto(C));
  return C;
}
