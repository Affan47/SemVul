hasFP(const MachineFunction &MF) const {
  const MachineFrameInfo *MFI = MF.getFrameInfo();
  const TargetRegisterInfo *TRI = STI.getRegisterInfo();

  return MF.getTarget().Options.DisableFramePointerElim(MF) ||
      MFI->hasVarSizedObjects() || MFI->isFrameAddressTaken() ||
      TRI->needsStackRealignment(MF);
}
