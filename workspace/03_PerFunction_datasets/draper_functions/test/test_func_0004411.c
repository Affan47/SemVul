outputLocation1(const Location &loc)
{
  const Origin *origin = loc.origin().pointer();
  const InputSourceOrigin *inputSourceOrigin;
  const ExternalInfo *info;
  Index index = loc.index();
  for (;;) {
    if (!origin)
      return;
    inputSourceOrigin = origin->asInputSourceOrigin();
    if (inputSourceOrigin) {
      info = inputSourceOrigin->externalInfo();
      if (info)
	break;
    }
    const Location &loc = origin->parent();
    index = loc.index();
    origin = loc.origin().pointer();
  }
  Offset off = inputSourceOrigin->startOffset(index);
  StorageObjectLocation soLoc;
  if (!ExtendEntityManager::externalize(info, off, soLoc))
    return;
  if (soLoc.lineNumber == (unsigned long)-1)
    return;
  if (soLoc.storageObjectSpec == lastSos_) {
    if (soLoc.lineNumber == lastLineno_)
      return;
    flushData();
    os() << locationCode << soLoc.lineNumber << nl;
    lastLineno_ = soLoc.lineNumber;
  }
  else {
    flushData();
    os() << locationCode << soLoc.lineNumber << space;
    outputString(soLoc.actualStorageId);
    os() << nl;
    lastLineno_ = soLoc.lineNumber;
    lastSos_ = soLoc.storageObjectSpec;
    lastLoc_ = loc;
  }
}
