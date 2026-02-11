getPrologueDeath(MachineFunction &MF, unsigned Reg) {
  if (Reg != AArch64::LR)
    return getKillRegState(true);


  bool LRLiveIn = MF.getRegInfo().isLiveIn(AArch64::LR);
  bool LRKill = !(LRLiveIn && MF.getFrameInfo()->isReturnAddressTaken());
  return getKillRegState(LRKill);
}
