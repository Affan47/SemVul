replaceSpecifier(NestedNameSpecifierLoc Loc,
                                    const std::string &Name)
{
  SourceRange LocRange = Loc.getLocalSourceRange();
  TransAssert((TheRewriter->getRangeSize(LocRange) != -1) &&
              "Bad NestedNameSpecifierLoc Range!");
  return !(TheRewriter->ReplaceText(LocRange, Name + "::"));
}
