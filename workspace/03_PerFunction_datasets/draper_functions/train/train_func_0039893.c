parseAttributeSpec(Boolean inDecl,
				   AttributeList &atts,
				   Boolean &netEnabling,
				   Ptr<AttributeDefinitionList> &newAttDef)

{
  unsigned specLength = 0;
  AttributeParameter::Type curParm;

  if (!parseAttributeParameter(inDecl, 0, curParm, netEnabling))
    return 0;
  while (curParm != AttributeParameter::end) {
    switch (curParm) {
    case AttributeParameter::name:
      {
	Text text;
	text.addChars(currentInput()->currentTokenStart(),
		      currentInput()->currentTokenLength(),
		      currentLocation());
	size_t nameMarkupIndex;
	if (currentMarkup())
	  nameMarkupIndex = currentMarkup()->size() - 1;
	text.subst(*syntax().generalSubstTable(), syntax().space());
	if (!parseAttributeParameter(inDecl, 1, curParm, netEnabling))
	  return 0;
	if (curParm == AttributeParameter::vi) {
	  specLength += text.size() + syntax().normsep();
	  if (!parseAttributeValueSpec(inDecl, text.string(), atts,
				       specLength, newAttDef))
	    return 0;

	  if (!parseAttributeParameter(inDecl, 0, curParm, netEnabling))
	    return 0;
	}
	else {
	  if (currentMarkup())
	    currentMarkup()->changeToAttributeValue(nameMarkupIndex);
	  if (!handleAttributeNameToken(text, atts, specLength))
	    return 0;
	}
      }
      break;
    case AttributeParameter::nameToken:
      {
	Text text;
	text.addChars(currentInput()->currentTokenStart(),
		      currentInput()->currentTokenLength(),
		      currentLocation());
	text.subst(*syntax().generalSubstTable(), syntax().space());
	if (!handleAttributeNameToken(text, atts, specLength))
	  return 0;
	if (!parseAttributeParameter(inDecl, 0, curParm, netEnabling))
	  return 0;
      }
      break;
    case AttributeParameter::recoverUnquoted:
      {
	if (!atts.recoverUnquoted(currentToken(), currentLocation(), *this)) {

	  currentInput()->endToken(1);
	  if (!atts.handleAsUnterminated(*this))
	    message(ParserMessages::attributeSpecCharacter,
		    StringMessageArg(currentToken()));
	  return 0;
	}
	if (!parseAttributeParameter(inDecl, 0, curParm, netEnabling))
	  return 0;
      }
      break;
    default:
      CANNOT_HAPPEN();
    }
  }
  atts.finish(*this);
  if (specLength > syntax().attsplen())
    message(ParserMessages::attsplen,
	    NumberMessageArg(syntax().attsplen()),
	    NumberMessageArg(specLength));
  return 1;
}
