computeIntervals(MachineRegisterInfo &MRI,
                            const TargetRegisterInfo &TRI,
                            LiveIntervals &LIS,
                            MachineDominatorTree &MDT,
                            UserValueScopes &UVS) {
  SmallVector<std::pair<SlotIndex, unsigned>, 16> Defs;


  for (LocMap::const_iterator I = locInts.begin(); I.valid(); ++I)
    if (I.value() != ~0u)
      Defs.push_back(std::make_pair(I.start(), I.value()));


  for (unsigned i = 0; i != Defs.size(); ++i) {
    SlotIndex Idx = Defs[i].first;
    unsigned LocNo = Defs[i].second;
    const MachineOperand &Loc = locations[LocNo];

    if (!Loc.isReg()) {
      extendDef(Idx, LocNo, nullptr, nullptr, nullptr, LIS, MDT, UVS);
      continue;
    }


    if (TargetRegisterInfo::isVirtualRegister(Loc.getReg())) {
      LiveInterval *LI = nullptr;
      const VNInfo *VNI = nullptr;
      if (LIS.hasInterval(Loc.getReg())) {
        LI = &LIS.getInterval(Loc.getReg());
        VNI = LI->getVNInfoAt(Idx);
      }
      SmallVector<SlotIndex, 16> Kills;
      extendDef(Idx, LocNo, LI, VNI, &Kills, LIS, MDT, UVS);
      if (LI)
        addDefsFromCopies(LI, LocNo, Kills, Defs, MRI, LIS);
      continue;
    }


    unsigned Unit = *MCRegUnitIterator(Loc.getReg(), &TRI);
    LiveRange *LR = &LIS.getRegUnit(Unit);
    const VNInfo *VNI = LR->getVNInfoAt(Idx);

    extendDef(Idx, LocNo, LR, VNI, nullptr, LIS, MDT, UVS);
  }


  for (LocMap::iterator I = locInts.begin(); I.valid();)
    if (I.value() == ~0u)
      I.erase();
    else
      ++I;
}
