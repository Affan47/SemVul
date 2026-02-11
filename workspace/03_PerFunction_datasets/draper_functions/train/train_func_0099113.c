runOnMachineFunction(MachineFunction &MF) {
  TRI = MF.getSubtarget().getRegisterInfo();
  LIS = &getAnalysis<LiveIntervals>();
  VRM = &getAnalysis<VirtRegMap>();

  unsigned NumRegUnits = TRI->getNumRegUnits();
  if (NumRegUnits != Matrix.size())
    Queries.reset(new LiveIntervalUnion::Query[NumRegUnits]);
  Matrix.init(LIUAlloc, NumRegUnits);


  invalidateVirtRegs();
  return false;
}
