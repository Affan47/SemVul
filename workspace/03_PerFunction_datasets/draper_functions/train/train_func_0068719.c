ParseBodyItem(Record *CurRec) {
  if (Lex.getCode() != tgtok::Let) {
    if (ParseDeclaration(CurRec, false) == 0)
      return true;

    if (Lex.getCode() != tgtok::semi)
      return TokError("expected ';' after declaration");
    Lex.Lex();
    return false;
  }


  if (Lex.Lex() != tgtok::Id)
    return TokError("expected field identifier after let");

  SMLoc IdLoc = Lex.getLoc();
  std::string FieldName = Lex.getCurStrVal();
  Lex.Lex();

  std::vector<unsigned> BitList;
  if (ParseOptionalBitList(BitList))
    return true;
  std::reverse(BitList.begin(), BitList.end());

  if (Lex.getCode() != tgtok::equal)
    return TokError("expected '=' in let expression");
  Lex.Lex();

  RecordVal *Field = CurRec->getValue(FieldName);
  if (Field == 0)
    return TokError("Value '" + FieldName + "' unknown!");

  RecTy *Type = Field->getType();

  Init *Val = ParseValue(CurRec, Type);
  if (Val == 0) return true;

  if (Lex.getCode() != tgtok::semi)
    return TokError("expected ';' after let expression");
  Lex.Lex();

  return SetValue(CurRec, IdLoc, FieldName, BitList, Val);
}
