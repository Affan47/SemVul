getRegPressureLimit(const TargetRegisterClass *RC,
                                         MachineFunction &MF) const {
  const TargetFrameLowering *TFI = MF.getTarget().getFrameLowering();

  switch (RC->getID()) {
  default:
    return 0;
  case ARM::tGPRRegClassID:
    return TFI->hasFP(MF) ? 4 : 5;
  case ARM::GPRRegClassID: {
    unsigned FP = TFI->hasFP(MF) ? 1 : 0;
    return 10 - FP - (STI.isR9Reserved() ? 1 : 0);
  }
  case ARM::SPRRegClassID:
  case ARM::DPRRegClassID:
    return 32 - 10;
  }
}
