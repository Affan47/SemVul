lexMIToken(
    StringRef Source, MIToken &Token,
    function_ref<void(StringRef::iterator Loc, const Twine &)> ErrorCallback) {
  auto C = skipComment(skipWhitespace(Cursor(Source)));
  if (C.isEOF()) {
    Token.reset(MIToken::Eof, C.remaining());
    return C.remaining();
  }

  if (Cursor R = maybeLexIntegerType(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexMachineBasicBlock(C, Token, ErrorCallback))
    return R.remaining();
  if (Cursor R = maybeLexIdentifier(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexJumpTableIndex(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexStackObject(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexFixedStackObject(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexConstantPoolItem(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexIRBlock(C, Token, ErrorCallback))
    return R.remaining();
  if (Cursor R = maybeLexIRValue(C, Token, ErrorCallback))
    return R.remaining();
  if (Cursor R = maybeLexRegister(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexGlobalValue(C, Token, ErrorCallback))
    return R.remaining();
  if (Cursor R = maybeLexExternalSymbol(C, Token, ErrorCallback))
    return R.remaining();
  if (Cursor R = maybeLexHexFloatingPointLiteral(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexNumericalLiteral(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexExlaim(C, Token, ErrorCallback))
    return R.remaining();
  if (Cursor R = maybeLexSymbol(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexNewline(C, Token))
    return R.remaining();
  if (Cursor R = maybeLexEscapedIRValue(C, Token, ErrorCallback))
    return R.remaining();

  Token.reset(MIToken::Error, C.remaining());
  ErrorCallback(C.location(),
                Twine("unexpected character '") + Twine(C.peek()) + "'");
  return C.remaining();
}
