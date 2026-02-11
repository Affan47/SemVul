handleBadStartTag(const ElementType *e,
			       StartElementEvent *event,
			       Boolean netEnabling)
{
  IList<Undo> undoList;
  IList<Event> eventList;
  keepMessages();
  for (;;) {
    Vector<const ElementType *> missing;
    findMissingTag(e, missing);
    if (missing.size() == 1) {
      queueElementEvents(eventList);
      const ElementType *m = missing[0];
      message(ParserMessages::missingElementInferred,
	      StringMessageArg(e->name()),
	      StringMessageArg(m->name()));
      AttributeList *attributes
	= allocAttributeList(m->attributeDef(), 1);

      attributes->finish(*this);
      StartElementEvent *inferEvent
	= new (eventAllocator()) StartElementEvent(m,
						   currentDtdPointer(),
						   attributes,
						   event->location(),
						   0);
      if (!currentElement().tryTransition(m))
	inferEvent->setIncluded();
      pushElementCheck(m, inferEvent, 0);
      if (!currentElement().tryTransition(e))
	event->setIncluded();
      pushElementCheck(e, event, netEnabling);
      return;
    }
    if (missing.size() > 0) {
      queueElementEvents(eventList);
      Vector<StringC> missingNames;
      for (size_t i = 0; i < missing.size(); i++)
	missingNames.push_back(missing[i]->name());
      message(ParserMessages::missingElementMultiple,
	      StringMessageArg(e->name()),
	      StringVectorMessageArg(missingNames));
      pushElementCheck(e, event, netEnabling);
      return;
    }
    if (!sd().omittag()
	|| !currentElement().isFinished()
	|| tagLevel() == 0
	|| !currentElement().type()->definition()->canOmitEndTag())
      break;
    EndElementEvent *endEvent
      = new (eventAllocator()) EndElementEvent(currentElement().type(),
					       currentDtdPointer(),
					       event->location(),
					       0);
    eventList.insert(endEvent);
    undoList.insert(new (internalAllocator()) UndoEndTag(popSaveElement()));
  }
  discardKeptMessages();
  undo(undoList);
  message(ParserMessages::elementNotAllowed, StringMessageArg(e->name()));


  (void)currentElement().tryTransition(e);
  pushElementCheck(e, event, netEnabling);
}
