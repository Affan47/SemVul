ParseDirectiveWeakref(StringRef, SMLoc) {


  StringRef AliasName;
  if (getParser().parseIdentifier(AliasName))
    return TokError("expected identifier in directive");

  if (getLexer().isNot(AsmToken::Comma))
    return TokError("expected a comma");

  Lex();

  StringRef Name;
  if (getParser().parseIdentifier(Name))
    return TokError("expected identifier in directive");

  MCSymbol *Alias = getContext().getOrCreateSymbol(AliasName);

  MCSymbol *Sym = getContext().getOrCreateSymbol(Name);

  getStreamer().EmitWeakReference(Alias, Sym);
  return false;
}
