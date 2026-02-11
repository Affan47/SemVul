getVirtRegFor(unsigned PReg) const {
  typedef MachineRegisterInfo::livein_iterator iterator;
  for (iterator I = MRI.livein_begin(), E = MRI.livein_end(); I != E; ++I) {
    if (I->first == PReg)
      return I->second;
  }
  return 0;
}
