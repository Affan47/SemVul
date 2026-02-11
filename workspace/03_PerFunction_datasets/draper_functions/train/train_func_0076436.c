substituteRegister(unsigned FromReg,
                                      unsigned ToReg,
                                      unsigned SubIdx,
                                      const TargetRegisterInfo &RegInfo) {
  if (TargetRegisterInfo::isPhysicalRegister(ToReg)) {
    if (SubIdx)
      ToReg = RegInfo.getSubReg(ToReg, SubIdx);
    for (MachineOperand &MO : operands()) {
      if (!MO.isReg() || MO.getReg() != FromReg)
        continue;
      MO.substPhysReg(ToReg, RegInfo);
    }
  } else {
    for (MachineOperand &MO : operands()) {
      if (!MO.isReg() || MO.getReg() != FromReg)
        continue;
      MO.substVirtReg(ToReg, SubIdx, RegInfo);
    }
  }
}
