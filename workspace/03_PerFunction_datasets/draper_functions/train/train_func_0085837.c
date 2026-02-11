cannotEliminateFrame(const MachineFunction &MF) const {
  const MachineFrameInfo *MFI = MF.getFrameInfo();

  if (MFI->hasCalls() || (MF.getTarget().Options.DisableFramePointerElim(MF) &&
                          MFI->adjustsStack()))
    return true;
  return MFI->hasVarSizedObjects() || MFI->isFrameAddressTaken();
}
