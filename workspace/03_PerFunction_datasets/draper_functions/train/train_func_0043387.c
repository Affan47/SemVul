doesSymbolRequireExternRelocation(const MCSymbolData *SD) {

  if (SD->Symbol->isUndefined())
    return true;


  if (SD->getFlags() & SF_WeakDefinition)
    return true;


  return false;
}
