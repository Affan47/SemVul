addNeededShortrefs(Dtd &dtd, const Syntax &syntax)
{
  if (!syntax.hasShortrefs())
    return;
  PackedBoolean delimRelevant[Syntax::nDelimGeneral];
  size_t i;
  for (i = 0; i < Syntax::nDelimGeneral; i++)
    delimRelevant[i] = 0;
  ModeInfo iter(mconnetMode, sd());
  TokenInfo ti;
  while (iter.nextToken(&ti)) {
    switch (ti.type) {
    case TokenInfo::delimType:
    case TokenInfo::delimDelimType:
    case TokenInfo::delimSetType:
      delimRelevant[ti.delim1] = 1;
      break;
    default:
      break;
    }
  }


  if (syntax.isValidShortref(syntax.delimGeneral(Syntax::dPIO)))
    dtd.addNeededShortref(syntax.delimGeneral(Syntax::dPIO));
  if (syntax.isValidShortref(syntax.delimGeneral(Syntax::dNET)))
    dtd.addNeededShortref(syntax.delimGeneral(Syntax::dNET));

  size_t nShortrefComplex = syntax.nDelimShortrefComplex();


  for (i = 0; i < nShortrefComplex; i++) {
    size_t j;
    for (j = 0; j < Syntax::nDelimGeneral; j++)
      if (delimRelevant[j]
	  && shortrefCanPreemptDelim(syntax.delimShortrefComplex(i),
				     syntax.delimGeneral(j),
				     0,
				     syntax)) {
	dtd.addNeededShortref(syntax.delimShortrefComplex(i));
	break;
      }
    for (j = 0; j < dtd.nShortref(); j++)
      if (shortrefCanPreemptDelim(syntax.delimShortrefComplex(i),
				  dtd.shortref(j),
				  1,
				  syntax)) {
	dtd.addNeededShortref(syntax.delimShortrefComplex(i));
	break;
      }
  }

}
