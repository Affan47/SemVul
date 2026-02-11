getFileSpecName (Object *fileSpec, Object *fileName)
{
  if (fileSpec->isString()) {
    fileSpec->copy(fileName);
    return gTrue;
  }

  if (fileSpec->isDict()) {
    fileSpec->dictLookup("UF", fileName);
    if (fileName->isString()) {
      return gTrue;
    }
    fileName->free();
    fileSpec->dictLookup("F", fileName);
    if (fileName->isString()) {
      return gTrue;
    }
    fileName->free();
    fileSpec->dictLookup("DOS", fileName);
    if (fileName->isString()) {
      return gTrue;
    }
    fileName->free();
    fileSpec->dictLookup("Mac", fileName);
    if (fileName->isString()) {
      return gTrue;
    }
    fileName->free();
    fileSpec->dictLookup("Unix", fileName);
    if (fileName->isString()) {
      return gTrue;
    }
    fileName->free();
  }
  return gFalse;
}
