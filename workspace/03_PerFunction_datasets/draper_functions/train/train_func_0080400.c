LexLineComment() {


  int CurChar = getNextChar();
  while (CurChar != '\n' && CurChar != '\r' && CurChar != EOF)
    CurChar = getNextChar();

  if (CurChar == EOF)
    return AsmToken(AsmToken::Eof, StringRef(CurPtr, 0));
  return AsmToken(AsmToken::EndOfStatement, StringRef(CurPtr, 0));
}
