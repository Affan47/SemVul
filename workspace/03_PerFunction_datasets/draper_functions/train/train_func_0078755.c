findSuperReg(const TargetRegisterClass *RC, unsigned SubReg,
                             unsigned SubIdx, const TargetRegisterInfo *TRI) {
  for (TargetRegisterClass::iterator I = RC->begin(), E = RC->end();
       I != E; ++I) {
    unsigned Reg = *I;
    if (TRI->getSubReg(Reg, SubIdx) == SubReg)
      return Reg;
  }
  return 0;
}
