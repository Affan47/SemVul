splitRegister(unsigned OldReg, ArrayRef<unsigned> NewRegs, LiveIntervals &LIS) {
  if (pImpl)
    static_cast<LDVImpl*>(pImpl)->splitRegister(OldReg, NewRegs);
}
