EndCOFFSymbolDef() {
  if (!CurSymbol)
    FatalError("ending symbol definition without starting one");
  CurSymbol = nullptr;
}
