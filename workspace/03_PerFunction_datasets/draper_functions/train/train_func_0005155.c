ConvertPatternToMatcher(const PatternToMatch &Pattern,
                                       unsigned Variant,
                                       const CodeGenDAGPatterns &CGP) {
  MatcherGen Gen(Pattern, CGP);


  if (Gen.EmitMatcherCode(Variant))
    return 0;


  Gen.EmitResultCode();


  return Gen.GetMatcher();
}
