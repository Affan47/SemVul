parseEmptyStartTag()
{
  if (options().warnEmptyTag)
    message(ParserMessages::emptyStartTag);

  const ElementType *e = 0;
  if (!sd().omittag())
    e = lastEndedElementType();
  else if (tagLevel() > 0)
    e = currentElement().type();
  if (!e)
    e = currentDtd().documentElementType();
  AttributeList *attributes = allocAttributeList(e->attributeDef(), 0);
  attributes->finish(*this);
  Markup *markup = startMarkup(eventsWanted().wantInstanceMarkup(),
			       currentLocation());
  if (markup) {
    markup->addDelim(Syntax::dSTAGO);
    markup->addDelim(Syntax::dTAGC);
  }
  acceptStartTag(e,
		 new (eventAllocator())
		   StartElementEvent(e,
				     currentDtdPointer(),
				     attributes,
				     markupLocation(),
				     markup),
		 0);
}
