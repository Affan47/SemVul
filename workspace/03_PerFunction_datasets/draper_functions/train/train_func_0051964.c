ParseDirectiveDef(StringRef, SMLoc) {
  StringRef SymbolName;

  if (getParser().parseIdentifier(SymbolName))
    return TokError("expected identifier in directive");

  MCSymbol *Sym = getContext().getOrCreateSymbol(SymbolName);

  getStreamer().BeginCOFFSymbolDef(Sym);

  Lex();
  return false;
}
