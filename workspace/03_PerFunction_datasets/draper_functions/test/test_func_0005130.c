ParseDirectiveType(StringRef, SMLoc) {
  StringRef Name;
  if (getParser().parseIdentifier(Name))
    return TokError("expected identifier in directive");


  MCSymbol *Sym = getContext().getOrCreateSymbol(Name);


  if (getLexer().is(AsmToken::Comma))
    Lex();

  if (getLexer().isNot(AsmToken::Identifier) &&
      getLexer().isNot(AsmToken::Hash) &&
      getLexer().isNot(AsmToken::Percent) &&
      getLexer().isNot(AsmToken::String)) {
    if (!getLexer().getAllowAtInIdentifier())
      return TokError("expected STT_<TYPE_IN_UPPER_CASE>, '#<type>', "
                      "'%<type>' or \"<type>\"");
    else if (getLexer().isNot(AsmToken::At))
      return TokError("expected STT_<TYPE_IN_UPPER_CASE>, '#<type>', '@<type>', "
                      "'%<type>' or \"<type>\"");
  }

  if (getLexer().isNot(AsmToken::String) &&
      getLexer().isNot(AsmToken::Identifier))
    Lex();

  SMLoc TypeLoc = getLexer().getLoc();

  StringRef Type;
  if (getParser().parseIdentifier(Type))
    return TokError("expected symbol type in directive");

  MCSymbolAttr Attr = MCAttrForString(Type);
  if (Attr == MCSA_Invalid)
    return Error(TypeLoc, "unsupported attribute in '.type' directive");

  if (getLexer().isNot(AsmToken::EndOfStatement))
    return TokError("unexpected token in '.type' directive");
  Lex();

  getStreamer().EmitSymbolAttribute(Sym, Attr);

  return false;
}
