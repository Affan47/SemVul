handleAttributeNameToken(Text &text,
					 AttributeList &atts,
					 unsigned &specLength)
{
  unsigned index;
  if (!atts.tokenIndex(text.string(), index)) {
    if (atts.handleAsUnterminated(*this))
      return 0;
    atts.noteInvalidSpec();
    message(ParserMessages::noSuchAttributeToken,
	    StringMessageArg(text.string()));
  }
  else if (sd().www() && !atts.tokenIndexUnique(text.string(), index)) {
    atts.noteInvalidSpec();
    message(ParserMessages::attributeTokenNotUnique,
	    StringMessageArg(text.string()));
  }
  else {
    if (!sd().attributeOmitName())
      message(ParserMessages::attributeNameShorttag);
    else if (options().warnMissingAttributeName)
      message(ParserMessages::missingAttributeName);
    atts.setSpec(index, *this);
    atts.setValueToken(index, text, *this, specLength);
  }
  return 1;
}
