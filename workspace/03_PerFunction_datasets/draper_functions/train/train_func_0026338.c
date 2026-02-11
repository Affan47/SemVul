isValidCandidate(const MachineBasicBlock *B)
      const {
  if (!B)
    return true;
  if (B->isEHPad() || B->hasAddressTaken())
    return false;
  if (B->succ_size() == 0)
    return false;

  for (auto &MI : *B) {
    if (MI.isDebugValue())
      continue;
    if (MI.isConditionalBranch())
      return false;
    unsigned Opc = MI.getOpcode();
    bool IsJMP = (Opc == Hexagon::J2_jump);
    if (!isPredicableStore(&MI) && !IsJMP && !isSafeToSpeculate(&MI))
      return false;


    for (ConstMIOperands MO(&MI); MO.isValid(); ++MO) {
      if (!MO->isReg() || !MO->isDef())
        continue;
      unsigned R = MO->getReg();
      if (!TargetRegisterInfo::isVirtualRegister(R))
        continue;
      if (MRI->getRegClass(R) != &Hexagon::PredRegsRegClass)
        continue;
      for (auto U = MRI->use_begin(R); U != MRI->use_end(); ++U)
        if (U->getParent()->isPHI())
          return false;
    }
  }
  return true;
}
