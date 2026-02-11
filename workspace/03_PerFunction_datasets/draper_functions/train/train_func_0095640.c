createEmptyIntervalFrom(unsigned OldReg) {
  unsigned VReg = MRI.createVirtualRegister(MRI.getRegClass(OldReg));
  if (VRM) {
    VRM->setIsSplitFromReg(VReg, VRM->getOriginal(OldReg));
  }
  LiveInterval &LI = LIS.createEmptyInterval(VReg);
  return LI;
}
