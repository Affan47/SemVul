LexDigit() {

  if (CurPtr[-1] != '0' || CurPtr[0] == '.') {
    while (isdigit(*CurPtr))
      ++CurPtr;


    if (*CurPtr == '.' || *CurPtr == 'e') {
      ++CurPtr;
      return LexFloatLiteral();
    }

    StringRef Result(TokStart, CurPtr - TokStart);

    long long Value;
    if (Result.getAsInteger(10, Value)) {


      unsigned long long UValue;
      if (Result.getAsInteger(10, UValue))
        return ReturnError(TokStart, "invalid decimal number");
      Value = (long long)UValue;
    }


    SkipIgnoredIntegerSuffix(CurPtr);

    return AsmToken(AsmToken::Integer, Result, Value);
  }

  if (*CurPtr == 'b') {
    ++CurPtr;

    if (!isdigit(CurPtr[0])) {
      --CurPtr;
      StringRef Result(TokStart, CurPtr - TokStart);
      return AsmToken(AsmToken::Integer, Result, 0);
    }
    const char *NumStart = CurPtr;
    while (CurPtr[0] == '0' || CurPtr[0] == '1')
      ++CurPtr;


    if (CurPtr == NumStart)
      return ReturnError(TokStart, "invalid binary number");

    StringRef Result(TokStart, CurPtr - TokStart);

    long long Value;
    if (Result.substr(2).getAsInteger(2, Value))
      return ReturnError(TokStart, "invalid binary number");


    SkipIgnoredIntegerSuffix(CurPtr);

    return AsmToken(AsmToken::Integer, Result, Value);
  }

  if (*CurPtr == 'x') {
    ++CurPtr;
    const char *NumStart = CurPtr;
    while (isxdigit(CurPtr[0]))
      ++CurPtr;


    if (CurPtr == NumStart)
      return ReturnError(CurPtr-2, "invalid hexadecimal number");

    unsigned long long Result;
    if (StringRef(TokStart, CurPtr - TokStart).getAsInteger(0, Result))
      return ReturnError(TokStart, "invalid hexadecimal number");


    SkipIgnoredIntegerSuffix(CurPtr);

    return AsmToken(AsmToken::Integer, StringRef(TokStart, CurPtr - TokStart),
                    (int64_t)Result);
  }


  while (*CurPtr >= '0' && *CurPtr <= '9')
    ++CurPtr;

  StringRef Result(TokStart, CurPtr - TokStart);
  long long Value;
  if (Result.getAsInteger(8, Value))
    return ReturnError(TokStart, "invalid octal number");


  SkipIgnoredIntegerSuffix(CurPtr);

  return AsmToken(AsmToken::Integer, Result, Value);
}
