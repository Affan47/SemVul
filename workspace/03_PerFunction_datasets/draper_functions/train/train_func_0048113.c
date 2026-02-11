ColorSlotsWithFreeRegs(SmallVector<int, 16> &SlotMapping,
                                   SmallVector<SmallVector<int, 4>, 16> &RevMap,
                                   BitVector &SlotIsReg) {
  if (!(ColorWithRegs || ColorWithRegsOpt) || !VRM->HasUnusedRegisters())
    return false;

  bool Changed = false;
  DEBUG(dbgs() << "Assigning unused registers to spill slots:\n");
  for (unsigned i = 0, e = SSIntervals.size(); i != e; ++i) {
    LiveInterval *li = SSIntervals[i];
    int SS = li->getStackSlotIndex();
    if (!UsedColors[SS] || li->weight < 20)


      continue;


    bool AllColored = true;
    SmallVector<unsigned, 4> ColoredRegs;
    for (unsigned j = 0, ee = RevMap[SS].size(); j != ee; ++j) {
      int RSS = RevMap[SS][j];
      const TargetRegisterClass *RC = LS->getIntervalRegClass(RSS);


      if (!RC) {
        AllColored = false;
        continue;
      }
      unsigned Reg = VRM->getFirstUnusedRegister(RC);
      if (!Reg) {
        AllColored = false;
        continue;
      }
      if (!AllMemRefsCanBeUnfolded(RSS)) {
        AllColored = false;
        continue;
      } else {
        DEBUG(dbgs() << "Assigning fi#" << RSS << " to "
                     << TRI->getName(Reg) << '\n');
        ColoredRegs.push_back(Reg);
        SlotMapping[RSS] = Reg;
        SlotIsReg.set(RSS);
        Changed = true;
      }
    }


    while (!ColoredRegs.empty()) {
      unsigned Reg = ColoredRegs.back();
      ColoredRegs.pop_back();
      VRM->setRegisterUsed(Reg);


      MRI->setPhysRegUsed(Reg);
      for (const unsigned *AS = TRI->getAliasSet(Reg); *AS; ++AS) {
        VRM->setRegisterUsed(*AS);
        MRI->setPhysRegUsed(*AS);
      }
    }

    if (AllColored) {
      MFI->RemoveStackObject(SS);
      ++NumEliminated;
    }
  }
  DEBUG(dbgs() << '\n');

  return Changed;
}
