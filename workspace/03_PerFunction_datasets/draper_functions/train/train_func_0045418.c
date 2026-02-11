hasLoopHazard(MachineInstr *MI) const {
  unsigned Reg = MI->getOperand(1).getReg();
  if (TargetRegisterInfo::isPhysicalRegister(Reg))
    return false;

  MachineBasicBlock *MBB = MI->getParent();
  MachineInstr *DefMI = MRI->getVRegDef(Reg);
  while (true) {
outer_continue:
    if (DefMI->getParent() != MBB)
      break;

    if (DefMI->isPHI()) {
      for (unsigned i = 1, e = DefMI->getNumOperands(); i < e; i += 2) {
        if (DefMI->getOperand(i + 1).getMBB() == MBB) {
          unsigned SrcReg = DefMI->getOperand(i).getReg();
          if (TargetRegisterInfo::isVirtualRegister(SrcReg)) {
            DefMI = MRI->getVRegDef(SrcReg);
            goto outer_continue;
          }
        }
      }
    } else if (DefMI->isCopyLike()) {
      Reg = DefMI->getOperand(1).getReg();
      if (TargetRegisterInfo::isVirtualRegister(Reg)) {
        DefMI = MRI->getVRegDef(Reg);
        continue;
      }
    } else if (DefMI->isInsertSubreg()) {
      Reg = DefMI->getOperand(2).getReg();
      if (TargetRegisterInfo::isVirtualRegister(Reg)) {
        DefMI = MRI->getVRegDef(Reg);
        continue;
      }
    }

    break;
  }

  return DefMI == MI;
}
