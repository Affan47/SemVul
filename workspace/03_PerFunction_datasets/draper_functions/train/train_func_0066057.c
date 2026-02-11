getExprForDwarfGlobalReference(const GlobalValue *GV, Mangler *Mang,
                               MachineModuleInfo *MMI, unsigned Encoding,
                               MCStreamer &Streamer) const {


  if (Encoding & (DW_EH_PE_indirect | DW_EH_PE_pcrel)) {
    const MCSymbol *Sym = Mang->getSymbol(GV);
    const MCExpr *Res =
      MCSymbolRefExpr::Create(Sym, MCSymbolRefExpr::VK_GOTPCREL, getContext());
    const MCExpr *Four = MCConstantExpr::Create(4, getContext());
    return MCBinaryExpr::CreateAdd(Res, Four, getContext());
  }

  return TargetLoweringObjectFileMachO::
    getExprForDwarfGlobalReference(GV, Mang, MMI, Encoding, Streamer);
}
