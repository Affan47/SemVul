isInvalidLoopOperation(const MachineInstr *MI,
                                                  bool IsInnerHWLoop) const {


  if (MI->getDesc().isCall() && MI->getOpcode() != Hexagon::CALLv3nr)
    return true;


  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg() || !MO.isDef())
      continue;
    unsigned R = MO.getReg();
    if (IsInnerHWLoop && (R == Hexagon::LC0 || R == Hexagon::SA0 ||
                          R == Hexagon::LC1 || R == Hexagon::SA1))
      return true;
    if (!IsInnerHWLoop && (R == Hexagon::LC1 || R == Hexagon::SA1))
      return true;
  }
  return false;
}
