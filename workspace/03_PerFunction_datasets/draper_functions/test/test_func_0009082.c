runOnMachineFunction(MachineFunction &MF) {
  DEBUG({
      dbgs() << "********** Stack Slot Coloring **********\n"
             << "********** Function: " << MF.getName() << '\n';
    });

  MFI = MF.getFrameInfo();
  TII = MF.getSubtarget().getInstrInfo();
  LS = &getAnalysis<LiveStacks>();
  MBFI = &getAnalysis<MachineBlockFrequencyInfo>();

  bool Changed = false;

  unsigned NumSlots = LS->getNumIntervals();
  if (NumSlots == 0)

    return false;


  if (MF.exposesReturnsTwice())
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

  return Changed;
}
