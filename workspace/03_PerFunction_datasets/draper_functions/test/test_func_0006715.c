SymbolValue(const MCSymbol &Sym,
                                      const MCAsmLayout &Layout) {
  if (Sym.isCommon() && Sym.isExternal())
    return Sym.getCommonAlignment();

  uint64_t Res;
  if (!Layout.getSymbolOffset(Sym, Res))
    return 0;

  if (Layout.getAssembler().isThumbFunc(&Sym))
    Res |= 1;

  return Res;
}
