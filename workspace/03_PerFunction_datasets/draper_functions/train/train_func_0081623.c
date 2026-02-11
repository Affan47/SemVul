CompareNumbers(const char *&F1P, const char *&F2P,
                           const char *F1End, const char *F2End,
                           double AbsTolerance, double RelTolerance,
                           std::string *ErrorMsg) {
  const char *F1NumEnd, *F2NumEnd;
  double V1 = 0.0, V2 = 0.0;


  while (isspace(*F1P) && F1P != F1End)
    ++F1P;
  while (isspace(*F2P) && F2P != F2End)
    ++F2P;


  if (!isNumberChar(*F1P) || !isNumberChar(*F2P)) {

    F1NumEnd = F1P;
    F2NumEnd = F2P;
  } else {


    V1 = strtod(F1P, const_cast<char**>(&F1NumEnd));
    V2 = strtod(F2P, const_cast<char**>(&F2NumEnd));

    if (*F1NumEnd == 'D' || *F1NumEnd == 'd') {

      SmallString<200> StrTmp(F1P, EndOfNumber(F1NumEnd)+1);

      StrTmp[static_cast<unsigned>(F1NumEnd-F1P)] = 'e';

      V1 = strtod(&StrTmp[0], const_cast<char**>(&F1NumEnd));
      F1NumEnd = F1P + (F1NumEnd-&StrTmp[0]);
    }

    if (*F2NumEnd == 'D' || *F2NumEnd == 'd') {

      SmallString<200> StrTmp(F2P, EndOfNumber(F2NumEnd)+1);

      StrTmp[static_cast<unsigned>(F2NumEnd-F2P)] = 'e';

      V2 = strtod(&StrTmp[0], const_cast<char**>(&F2NumEnd));
      F2NumEnd = F2P + (F2NumEnd-&StrTmp[0]);
    }
  }

  if (F1NumEnd == F1P || F2NumEnd == F2P) {
    if (ErrorMsg) {
      *ErrorMsg = "FP Comparison failed, not a numeric difference between '";
      *ErrorMsg += F1P[0];
      *ErrorMsg += "' and '";
      *ErrorMsg += F2P[0];
      *ErrorMsg += "'";
    }
    return true;
  }


  if (AbsTolerance < std::abs(V1-V2)) {

    double Diff;
    if (V2)
      Diff = std::abs(V1/V2 - 1.0);
    else if (V1)
      Diff = std::abs(V2/V1 - 1.0);
    else
      Diff = 0;
    if (Diff > RelTolerance) {
      if (ErrorMsg) {
        raw_string_ostream(*ErrorMsg)
          << "Compared: " << V1 << " and " << V2 << '\n'
          << "abs. diff = " << std::abs(V1-V2) << " rel.diff = " << Diff << '\n'
          << "Out of tolerance: rel/abs: " << RelTolerance << '/'
          << AbsTolerance;
      }
      return true;
    }
  }


  F1P = F1NumEnd;  F2P = F2NumEnd;
  return false;
}
