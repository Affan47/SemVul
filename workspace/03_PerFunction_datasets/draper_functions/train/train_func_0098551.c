addSymbol(Attribute name, const Symbol &symbol)
{
  assert(name.isSymbolic());
  iSymbols[name.index()] = symbol;
}
