GenerateSymbolicOffsets(LSRUse &LU, unsigned LUIdx,
                                          Formula Base) {

  if (Base.AM.BaseGV) return;

  for (size_t i = 0, e = Base.BaseRegs.size(); i != e; ++i) {
    const SCEV *G = Base.BaseRegs[i];
    GlobalValue *GV = ExtractSymbol(G, SE);
    if (G->isZero() || !GV)
      continue;
    Formula F = Base;
    F.AM.BaseGV = GV;
    if (!isLegalUse(F.AM, LU.MinOffset, LU.MaxOffset,
                    LU.Kind, LU.AccessTy, TLI))
      continue;
    F.BaseRegs[i] = G;
    (void)InsertFormula(LU, LUIdx, F);
  }
}
