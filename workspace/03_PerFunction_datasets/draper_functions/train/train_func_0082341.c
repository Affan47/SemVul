ParseSubMultiClassReference(MultiClass *CurMC) {
  SubMultiClassReference Result;
  Result.RefLoc = Lex.getLoc();

  Result.MC = ParseMultiClassID();
  if (Result.MC == 0) return Result;


  if (Lex.getCode() != tgtok::less)
    return Result;
  Lex.Lex();

  if (Lex.getCode() == tgtok::greater) {
    TokError("subclass reference requires a non-empty list of template values");
    Result.MC = 0;
    return Result;
  }

  Result.TemplateArgs = ParseValueList(&CurMC->Rec, &Result.MC->Rec);
  if (Result.TemplateArgs.empty()) {
    Result.MC = 0;
    return Result;
  }

  if (Lex.getCode() != tgtok::greater) {
    TokError("expected '>' in template value list");
    Result.MC = 0;
    return Result;
  }
  Lex.Lex();

  return Result;
}
