CommuteChangesDestination(MachineInstr *DefMI,
                                      const TargetInstrDesc &TID,
                                      unsigned SrcReg,
                                      const TargetInstrInfo *TII,
                                      unsigned &DstIdx) {
  if (TID.getNumDefs() != 1 && TID.getNumOperands() != 3)
    return false;
  if (!DefMI->getOperand(1).isReg() ||
      DefMI->getOperand(1).getReg() != SrcReg)
    return false;
  unsigned DefIdx;
  if (!DefMI->isRegTiedToDefOperand(1, &DefIdx) || DefIdx != 0)
    return false;
  unsigned SrcIdx1, SrcIdx2;
  if (!TII->findCommutedOpIndices(DefMI, SrcIdx1, SrcIdx2))
    return false;
  if (SrcIdx1 == 1 && SrcIdx2 == 2) {
    DstIdx = 2;
    return true;
  }
  return false;
}
