isCopyToReg(MachineInstr &MI, const TargetInstrInfo *TII,
                        unsigned &SrcReg, unsigned &DstReg,
                        bool &IsSrcPhys, bool &IsDstPhys) {
  SrcReg = 0;
  DstReg = 0;
  if (MI.isCopy()) {
    DstReg = MI.getOperand(0).getReg();
    SrcReg = MI.getOperand(1).getReg();
  } else if (MI.isInsertSubreg() || MI.isSubregToReg()) {
    DstReg = MI.getOperand(0).getReg();
    SrcReg = MI.getOperand(2).getReg();
  } else
    return false;

  IsSrcPhys = TargetRegisterInfo::isPhysicalRegister(SrcReg);
  IsDstPhys = TargetRegisterInfo::isPhysicalRegister(DstReg);
  return true;
}
