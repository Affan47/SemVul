operator>=(const MSSymbol& aSymbol_) const
{
  if (_atom!=MSNullAtom&&aSymbol_._atom!=MSNullAtom)
   {
     return MSBoolean(strcmp(symbolName(),aSymbol_.symbolName())>=0);
   }
  return MSBoolean(_atom>=aSymbol_._atom);
}
