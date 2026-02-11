checkNmchars(const ISet<Char> &set, const Syntax &syntax)
{
  Boolean valid = 1;
  ISet<WideChar> bad;
  intersectCharSets(set, *syntax.charSet(Syntax::nameStart), bad);
  if (!bad.isEmpty()) {
    message(ParserMessages::nmcharLetter, CharsetMessageArg(bad));
    valid = 0;
    bad.clear();
  }
  intersectCharSets(set, *syntax.charSet(Syntax::digit), bad);
  if (!bad.isEmpty()) {
    message(ParserMessages::nmcharDigit, CharsetMessageArg(bad));
    valid = 0;
    bad.clear();
  }
  Char funChar;
  if (syntax.getStandardFunction(Syntax::fRE, funChar)
      && set.contains(funChar)) {
    message(ParserMessages::nmcharRe, NumberMessageArg(funChar));
    valid = 0;
  }
  if (syntax.getStandardFunction(Syntax::fRS, funChar)
      && set.contains(funChar)) {
    message(ParserMessages::nmcharRs, NumberMessageArg(funChar));
    valid = 0;
  }
  if (syntax.getStandardFunction(Syntax::fSPACE, funChar)
      && set.contains(funChar)) {
    message(ParserMessages::nmcharSpace, NumberMessageArg(funChar));
    valid = 0;
  }
  intersectCharSets(set, *syntax.charSet(Syntax::sepchar), bad);
  if (!bad.isEmpty()) {
    message(ParserMessages::nmcharSepchar, CharsetMessageArg(bad));
    valid = 0;
  }
  return valid;
}
