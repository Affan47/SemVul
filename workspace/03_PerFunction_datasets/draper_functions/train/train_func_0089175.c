locationHeader(const Origin *origin,
						    Index index,
						    Offset &off)
{
   if (!(options_ & openEntities)) {
    while (origin) {
      const ExternalInfo *externalInfo = origin->externalInfo();
      if (externalInfo) {
  	off = origin->startOffset(index);
	return externalInfo;
      }
      const Location &loc = origin->parent();
      if (loc.origin().isNull()) {
	if (!origin->defLocation(origin->startOffset(index), origin, index))
	  break;
      }
      else {
	index = loc.index() + origin->refLength();
	origin = loc.origin().pointer();
      }
    }
  }
  else {
    Boolean doneHeader = 0;
    while (origin) {
      if (origin->entityName() || origin->parent().origin().isNull()) {
	if (!doneHeader) {
	  Offset parentOff;
	  const Location &parentLoc = origin->parent();
	  const ExternalInfo *parentInfo
	    = locationHeader(parentLoc.origin().pointer(),
			     parentLoc.index() + origin->refLength(),
			     parentOff);
	  if (parentInfo) {
	    StringC text;
	    if (getMessageText(origin->entityName()
			       ? MessageReporterMessages::inNamedEntity
			       : MessageReporterMessages::inUnnamedEntity,
				text)) {
	      for (size_t i = 0; i < text.size(); i++) {
		if (text[i] == '%') {
		  if (i + 1 < text.size()) {
		    i++;
		    if (text[i] == '1')
		      os() << *origin->entityName();
		    else if (text[i] == '2')
		      printLocation(parentInfo, parentOff);
		    else if (text[i] >= '3' && text[i] <= '9')
		      ;
		    else
		      os().put(text[i]);
		  }
		}
		else
		  os().put(text[i]);
	      }
	      os() << nl;
	    }
	  }
	  doneHeader = 1;
	}
	off = origin->startOffset(index);
	const ExternalInfo *externalInfo = origin->externalInfo();
	if (externalInfo)
	  return externalInfo;
	if (!origin->defLocation(off, origin, index))
	  break;
      }
      else {
	const Location &loc = origin->parent();
	index = loc.index() + origin->refLength();
	origin = loc.origin().pointer();
      }
    }
  }
  return 0;
}
