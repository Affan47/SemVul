ParseDirectiveLEB128(StringRef DirName, SMLoc) {
  getParser().CheckForValidSection();

  const MCExpr *Value;

  if (getParser().ParseExpression(Value))
    return true;

  if (getLexer().isNot(AsmToken::EndOfStatement))
    return TokError("unexpected token in directive");

  if (DirName[1] == 's')
    getStreamer().EmitSLEB128Value(Value);
  else
    getStreamer().EmitULEB128Value(Value);

  return false;
}
