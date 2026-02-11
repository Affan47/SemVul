EmitDwarfAdvanceLineAddr(int64_t LineDelta,
                                                const MCSymbol *LastLabel,
                                                const MCSymbol *Label,
                                                unsigned PointerSize) {
  if (!LastLabel) {
    emitDwarfSetLineAddr(*this, Assembler->getDWARFLinetableParams(), LineDelta,
                         Label, PointerSize);
    return;
  }
  const MCExpr *AddrDelta = buildSymbolDiff(*this, Label, LastLabel);
  int64_t Res;
  if (AddrDelta->evaluateAsAbsolute(Res, getAssembler())) {
    MCDwarfLineAddr::Emit(this, Assembler->getDWARFLinetableParams(), LineDelta,
                          Res);
    return;
  }
  insert(new MCDwarfLineAddrFragment(LineDelta, *AddrDelta));
}
