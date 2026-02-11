parseAttributeParameter(Boolean inDecl,
					Boolean allowVi,
					AttributeParameter::Type &result,
					Boolean &netEnabling)
{
  Mode mode = inDecl ? asMode : tagMode;
  Token token = getToken(mode);
  Markup *markup = currentMarkup();
  if (markup) {
    while (token == tokenS) {
      markup->addS(currentChar());
      token = getToken(mode);
    }
  }
  else {
    while (token == tokenS)
      token = getToken(mode);
  }
  switch (token) {
  case tokenUnrecognized:
    if (reportNonSgmlCharacter())
      return 0;
    extendUnquotedAttributeValue();
    result = AttributeParameter::recoverUnquoted;
    break;
  case tokenEe:
    message(ParserMessages::attributeSpecEntityEnd);
    return 0;
  case tokenEtago:
  case tokenStago:
    if (!sd().startTagUnclosed())
      message(ParserMessages::unclosedStartTagShorttag);
    result = AttributeParameter::end;
    currentInput()->ungetToken();
    netEnabling = 0;
    break;
  case tokenNestc:
    if (markup)
      markup->addDelim(Syntax::dNESTC);
    switch (sd().startTagNetEnable()) {
    case Sd::netEnableNo:
      message(ParserMessages::netEnablingStartTagShorttag);
      break;
    case Sd::netEnableImmednet:
      if (getToken(econnetMode) != tokenNet)
	message(ParserMessages::nestcWithoutNet);
      currentInput()->ungetToken();
      break;
    case Sd::netEnableAll:
      break;
    }
    netEnabling = 1;
    result = AttributeParameter::end;
    break;
  case tokenTagc:
    if (markup)
      markup->addDelim(Syntax::dTAGC);
    netEnabling = 0;
    result = AttributeParameter::end;
    break;
  case tokenDsc:
    if (markup)
      markup->addDelim(Syntax::dDSC);
    result = AttributeParameter::end;
    break;
  case tokenNameStart:
    extendNameToken(syntax().namelen(), ParserMessages::nameTokenLength);
    if (markup)
      markup->addName(currentInput());
    result = AttributeParameter::name;
    break;
  case tokenDigit:
  case tokenLcUcNmchar:
    extendNameToken(syntax().namelen(), ParserMessages::nameTokenLength);
    if (markup)
      markup->addName(currentInput());
    result = AttributeParameter::nameToken;
    break;
  case tokenLit:
  case tokenLita:
    message(allowVi
	    ? ParserMessages::attributeSpecLiteral
	    : ParserMessages::attributeSpecNameTokenExpected);
    return 0;
  case tokenVi:
    if (!allowVi) {
      message(ParserMessages::attributeSpecNameTokenExpected);
      return 0;
    }
    if (markup)
      markup->addDelim(Syntax::dVI);
    result = AttributeParameter::vi;
    break;
  default:
    CANNOT_HAPPEN();
  }
  return 1;
}
