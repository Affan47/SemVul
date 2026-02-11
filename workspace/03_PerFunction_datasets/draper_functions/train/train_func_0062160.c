ParseDirectiveSubsection(StringRef, SMLoc) {
  const MCExpr *Subsection = nullptr;
  if (getLexer().isNot(AsmToken::EndOfStatement)) {
    if (getParser().parseExpression(Subsection))
     return true;
  }

  if (getLexer().isNot(AsmToken::EndOfStatement))
    return TokError("unexpected token in directive");

  getStreamer().SubSection(Subsection);
  return false;
}
