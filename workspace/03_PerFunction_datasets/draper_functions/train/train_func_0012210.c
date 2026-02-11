parseExceptions(unsigned declInputLevel,
				Ptr<ElementDefinition> &def)
{
  Param parm;
  static AllowedParams
    allowExceptionsMdc(Param::mdc, Param::exclusions, Param::inclusions);
  if (!parseParam(allowExceptionsMdc, declInputLevel, parm))
    return 0;
  if (parm.type == Param::exclusions) {
    if (options().warnExclusion)
      message(ParserMessages::exclusion);
    def->setExclusions(parm.elementVector);
    static AllowedParams allowInclusionsMdc(Param::mdc, Param::inclusions);
    if (!parseParam(allowInclusionsMdc, declInputLevel, parm))
      return 0;
  }
  if (parm.type == Param::inclusions) {
    if (options().warnInclusion)
      message(ParserMessages::inclusion);
    def->setInclusions(parm.elementVector);
    size_t nI = def->nInclusions();
    size_t nE = def->nExclusions();
    if (nE) {
      for (size_t i = 0; i < nI; i++) {
	const ElementType *e = def->inclusion(i);
	for (size_t j = 0; j < nE; j++)
	  if (def->exclusion(j) == e)
	    message(ParserMessages::excludeIncludeSame,
		    StringMessageArg(e->name()));
      }
    }
    if (!parseParam(allowMdc, declInputLevel, parm))
      return 0;
  }
  return 1;
}
