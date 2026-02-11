charNameToUniv(Sd &sd, const StringC &name)
{
  UnivChar univ;
  if (entityCatalog().lookupChar(name, sd.internalCharset(), messenger(), univ))
    return univ;
  else
    return sd.nameToUniv(name);
}
