checkFnHasLiveInYmm(MachineRegisterInfo &MRI) {
  for (MachineRegisterInfo::livein_iterator I = MRI.livein_begin(),
       E = MRI.livein_end(); I != E; ++I)
    if (isYmmReg(I->first))
      return true;

  return false;
}
