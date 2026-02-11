ParseDirectiveCFISections(StringRef,
                                                 SMLoc DirectiveLoc) {
  StringRef Name;
  bool EH = false;
  bool Debug = false;

  if (getParser().ParseIdentifier(Name))
    return TokError("Expected an identifier");

  if (Name == ".eh_frame")
    EH = true;
  else if (Name == ".debug_frame")
    Debug = true;

  if (getLexer().is(AsmToken::Comma)) {
    Lex();

    if (getParser().ParseIdentifier(Name))
      return TokError("Expected an identifier");

    if (Name == ".eh_frame")
      EH = true;
    else if (Name == ".debug_frame")
      Debug = true;
  }

  getStreamer().EmitCFISections(EH, Debug);

  return false;
}
