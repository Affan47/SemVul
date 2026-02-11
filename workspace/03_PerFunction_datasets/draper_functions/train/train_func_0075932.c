LexIdentifier() {

  const char *IdentStart = TokStart;


  while (isalpha(*CurPtr) || isdigit(*CurPtr) || *CurPtr == '_')
    ++CurPtr;


  StringRef Str(IdentStart, CurPtr-IdentStart);

  if (Str == "include") {
    if (LexInclude()) return tgtok::Error;
    return Lex();
  }

  tgtok::TokKind Kind = StringSwitch<tgtok::TokKind>(Str)
    .Case("int", tgtok::Int)
    .Case("bit", tgtok::Bit)
    .Case("bits", tgtok::Bits)
    .Case("string", tgtok::String)
    .Case("list", tgtok::List)
    .Case("code", tgtok::Code)
    .Case("dag", tgtok::Dag)
    .Case("class", tgtok::Class)
    .Case("def", tgtok::Def)
    .Case("defm", tgtok::Defm)
    .Case("multiclass", tgtok::MultiClass)
    .Case("field", tgtok::Field)
    .Case("let", tgtok::Let)
    .Case("in", tgtok::In)
    .Default(tgtok::Id);

  if (Kind == tgtok::Id)
    CurStrVal.assign(Str.begin(), Str.end());
  return Kind;
}
