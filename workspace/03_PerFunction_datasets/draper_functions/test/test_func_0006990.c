LexIdentifier() {

  if (CurPtr[-1] == '.' && isdigit(*CurPtr)) {

    while (isdigit(*CurPtr))
      ++CurPtr;
    if (*CurPtr == 'e' || *CurPtr == 'E' ||
        !IsIdentifierChar(*CurPtr, AllowAtInIdentifier))
      return LexFloatLiteral();
  }

  while (IsIdentifierChar(*CurPtr, AllowAtInIdentifier))
    ++CurPtr;


  if (CurPtr == TokStart+1 && TokStart[0] == '.')
    return AsmToken(AsmToken::Dot, StringRef(TokStart, 1));

  return AsmToken(AsmToken::Identifier, StringRef(TokStart, CurPtr - TokStart));
}
