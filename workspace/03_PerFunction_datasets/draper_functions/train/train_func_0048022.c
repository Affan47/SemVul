visitMachineBundleAfter(const MachineInstr *MI) {
  BBInfo &MInfo = MBBInfoMap[MI->getParent()];
  set_union(MInfo.regsKilled, regsKilled);
  set_subtract(regsLive, regsKilled); regsKilled.clear();

  while (!regMasks.empty()) {
    const uint32_t *Mask = regMasks.pop_back_val();
    for (RegSet::iterator I = regsLive.begin(), E = regsLive.end(); I != E; ++I)
      if (TargetRegisterInfo::isPhysicalRegister(*I) &&
          MachineOperand::clobbersPhysReg(Mask, *I))
        regsDead.push_back(*I);
  }
  set_subtract(regsLive, regsDead);   regsDead.clear();
  set_union(regsLive, regsDefined);   regsDefined.clear();
}
