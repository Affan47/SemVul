getAsUnsignedInteger(StringRef Str, unsigned Radix,
                                unsigned long long &Result) {

  if (Radix == 0)
    Radix = GetAutoSenseRadix(Str);


  if (Str.empty()) return true;


  Result = 0;
  while (!Str.empty()) {
    unsigned CharVal;
    if (Str[0] >= '0' && Str[0] <= '9')
      CharVal = Str[0]-'0';
    else if (Str[0] >= 'a' && Str[0] <= 'z')
      CharVal = Str[0]-'a'+10;
    else if (Str[0] >= 'A' && Str[0] <= 'Z')
      CharVal = Str[0]-'A'+10;
    else
      return true;


    if (CharVal >= Radix)
      return true;


    unsigned long long PrevResult = Result;
    Result = Result*Radix+CharVal;


    if (Result/Radix < PrevResult)
      return true;

    Str = Str.substr(1);
  }

  return false;
}
