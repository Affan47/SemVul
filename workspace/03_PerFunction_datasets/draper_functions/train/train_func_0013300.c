getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = MF.getTarget().getFrameLowering();

  if (TFI->hasFP(MF))
    return FramePtr;
  return ARM::SP;
}
