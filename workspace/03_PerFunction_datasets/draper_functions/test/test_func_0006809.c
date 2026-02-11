shouldJoinPhys(CoalescerPair &CP) {
  bool Allocatable = LIS->isAllocatable(CP.getDstReg());
  LiveInterval &JoinVInt = LIS->getInterval(CP.getSrcReg());


  if (!Allocatable && CP.isFlipped() && JoinVInt.containsOneValue())
    return true;

  if (!EnablePhysicalJoin) {
    DEBUG(dbgs() << "\tPhysreg joins disabled.\n");
    return false;
  }


  if (!Allocatable) {
    DEBUG(dbgs() << "\tRegister is an unallocatable physreg.\n");
    return false;
  }


  if (LIS->hasInterval(CP.getDstReg()) &&
      LIS->getInterval(CP.getDstReg()).ranges.size() > 1000) {
    ++numAborts;
    DEBUG(dbgs()
          << "\tPhysical register live interval too complicated, abort!\n");
    return false;
  }


  if (!CP.isPartial()) {
    const TargetRegisterClass *RC = MRI->getRegClass(CP.getSrcReg());
    unsigned Threshold = RegClassInfo.getNumAllocatableRegs(RC) * 2;
    unsigned Length = LIS->getApproximateInstructionCount(JoinVInt);
    if (Length > Threshold) {
      ++numAborts;
      DEBUG(dbgs() << "\tMay tie down a physical register, abort!\n");
      return false;
    }
  }
  return true;
}
