runOnMachineFunction(MachineFunction &MF) {
  DEBUG({
      dbgs() << "********** Stack Slot Coloring **********\n"
             << "********** Function: "
             << MF.getFunction()->getName() << '\n';
    });

  MFI = MF.getFrameInfo();
  MRI = &MF.getRegInfo();
  TII = MF.getTarget().getInstrInfo();
  TRI = MF.getTarget().getRegisterInfo();
  LS = &getAnalysis<LiveStacks>();
  VRM = &getAnalysis<VirtRegMap>();
  loopInfo = &getAnalysis<MachineLoopInfo>();

  bool Changed = false;

  unsigned NumSlots = LS->getNumIntervals();
  if (NumSlots < 2) {
    if (NumSlots == 0 || !VRM->HasUnusedRegisters())

      return false;
  }


  if (MF.callsSetJmp())
    return false;


  ScanForSpillSlotRefs(MF);
  InitializeSlots();
  Changed = ColorSlots(MF);

  NextColor = -1;
  SSIntervals.clear();
  for (unsigned i = 0, e = SSRefs.size(); i != e; ++i)
    SSRefs[i].clear();
  SSRefs.clear();
  OrigAlignments.clear();
  OrigSizes.clear();
  AllColors.clear();
  UsedColors.clear();
  for (unsigned i = 0, e = Assignments.size(); i != e; ++i)
    Assignments[i].clear();
  Assignments.clear();

  if (Changed) {
    for (MachineFunction::iterator I = MF.begin(), E = MF.end(); I != E; ++I)
      Changed |= RemoveDeadStores(I);
  }

  return Changed;
}
