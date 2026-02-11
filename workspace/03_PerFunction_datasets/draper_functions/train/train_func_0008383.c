mayNeedRelaxation(const MCInst &Inst) const {
  if (getRelaxedOpcode(Inst.getOpcode()) != Inst.getOpcode())
    return true;
  return false;
}
