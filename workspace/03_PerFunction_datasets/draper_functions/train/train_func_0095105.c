AddDReg(MachineInstrBuilder &MIB,
                             unsigned Reg, unsigned SubIdx, unsigned State,
                             const TargetRegisterInfo *TRI) {
  if (!SubIdx)
    return MIB.addReg(Reg, State);

  if (TargetRegisterInfo::isPhysicalRegister(Reg))
    return MIB.addReg(TRI->getSubReg(Reg, SubIdx), State);
  return MIB.addReg(Reg, State, SubIdx);
}
