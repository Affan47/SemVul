parseDirectiveSyntax(SMLoc L) {
  const AsmToken &Tok = Parser.getTok();
  if (Tok.isNot(AsmToken::Identifier))
    return Error(L, "unexpected token in .syntax directive");
  StringRef Mode = Tok.getString();
  if (Mode == "unified" || Mode == "UNIFIED")
    Parser.Lex();
  else if (Mode == "divided" || Mode == "DIVIDED")
    return Error(L, "'.syntax divided' arm asssembly not supported");
  else
    return Error(L, "unrecognized syntax mode in .syntax directive");

  if (getLexer().isNot(AsmToken::EndOfStatement))
    return Error(Parser.getTok().getLoc(), "unexpected token in directive");
  Parser.Lex();


  return false;
}
