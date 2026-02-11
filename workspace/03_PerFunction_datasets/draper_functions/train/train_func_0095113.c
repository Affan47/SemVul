isReallyTriviallyReMaterializableGeneric(const MachineInstr *MI,
                                         AliasAnalysis *AA) const {
  const MachineFunction &MF = *MI->getParent()->getParent();
  const MachineRegisterInfo &MRI = MF.getRegInfo();


  if (!MI->getNumOperands() || !MI->getOperand(0).isReg())
    return false;
  unsigned DefReg = MI->getOperand(0).getReg();


  if (TargetRegisterInfo::isVirtualRegister(DefReg) &&
      MI->getOperand(0).getSubReg() && MI->readsVirtualRegister(DefReg))
    return false;


  int FrameIdx = 0;
  if (isLoadFromStackSlot(MI, FrameIdx) &&
      MF.getFrameInfo()->isImmutableObjectIndex(FrameIdx))
    return true;


  if (MI->isNotDuplicable() || MI->mayStore() ||
      MI->hasUnmodeledSideEffects())
    return false;


  if (MI->isInlineAsm())
    return false;


  if (MI->mayLoad() && !MI->isInvariantLoad(AA))
    return false;


  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg()) continue;
    unsigned Reg = MO.getReg();
    if (Reg == 0)
      continue;


    if (TargetRegisterInfo::isPhysicalRegister(Reg)) {
      if (MO.isUse()) {


        if (!MRI.isConstantPhysReg(Reg, MF))
          return false;
      } else {

        return false;
      }
      continue;
    }


    if (MO.isDef() && Reg != DefReg)
      return false;


    if (MO.isUse())
      return false;
  }


  return true;
}
